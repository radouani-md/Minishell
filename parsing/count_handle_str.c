/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_handle_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:02:37 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/14 22:51:33 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_node(t_node **arg)
{
	t_node	*tmp;
	t_node	*tmp1;

	tmp = *arg;
	tmp1 = NULL;
	while (tmp)
	{
		if (tmp->data[0] == '\0' && tmp->type != 2
			&& tmp->type != 4 && tmp->type != 1337)
		{
			if (!(*arg)->next)
			{
				*arg = NULL;
			}
			else if (!tmp1)
			{
				*arg = tmp->next;
			}
			else
				tmp1->next = tmp->next;
		}
		tmp1 = tmp;
		tmp = tmp->next;
	}
}


void	handle_multiple_quotes1(char *input, int *i, t_ha *handel, int *col)
{
	(*col)++;
	if (((input[*i] == '\"') || input[*i] == '\'') && input[(*i) + 1])
	{
		(*i)++;
		if (input[*i])
		{
			handel->read_index = *i;
			if (input[handel->read_index] == '\"')
				handel->quote_count1 = 1;
			else if (input[handel->read_index] == '\'')
				handel->q = 1;
			else if ((input[*i] != ' ' || input[*i] == '\t') && input[*i] != '>'
				&& input[*i] != '<' && input[*i] != '|' && input[*i])
			{
				(*i)++;
				(*col)++;
				handel->quote_count1 = 1;
				handel->q = 1;
				handel->read_index = *i;
			}
		}
	}
	else
		handel->read_index = ++(*i);
}

int	handel_qoutation1(char *input, int *i, t_ha *handel, int *col)
{
	if (input[handel->read_index] == '\"' && input[*i] == '\"')
		(handel->quote_count1)++;
	if (input[handel->read_index] == '\'' && input[*i] == '\'')
		(handel->q)++;
	while ((handel->quote_count1 % 2 == 0 && input[handel->read_index] == '\"')
		|| (handel->q % 2 == 0 && input[handel->read_index] == '\''))
	{
		if (*i != handel->read_index
			&& ((input[*i] == '\"' && input[handel->read_index] == '\"')
				|| (input[*i] == '\'' && input[handel->read_index] == '\'')))
		{
			break ;
		}
		(*i)++;
		(*col)++;
		if (!input[*i])
		{
			write(2, "eroor\n", 7);
			return (0);
		}
	}
	return (1);
}

int	ft_ft1(char *input, int *i, t_ha *handel, int *col)
{
	handel->read_index = *i;
	while (input[*i])
	{
		if (!handel_qoutation1(input, i, handel, col))
			return (0);
		handle_multiple_quotes1(input, i, handel, col);
		if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
			break ;
	}
	return (1);
}

int	count_handle_str(char *input, int i)
{
	t_ha	*handel;
	int		col;

	col = 0;
	handel = helper_varia(0);
	while (input[i] && (((input[i] != ' ' && input[i] != '\t')
				&& input[i] != '|' && input[i] != '>' && input[i] != '<')
			|| handel->dbl_qte % 2 == 1 || handel->snl_qte % 2 == 1))
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			conut_dabel_singel_qoutition(input[i], handel);
			col++;
			i++;
		}
		else
		{
			col++;
			i++;
		}
		if (input[i] == '\0'
			&& (handel->dbl_qte % 2 == 1 || handel->snl_qte % 2 == 1))
			return (write(2, "bash : syntax error\n", 20), col);
	}
	return (col);
}
