/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_handle_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:02:37 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/09 22:07:25 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_multiple_quotes1(char *input, int *i, t_handel *handel, int *col)
{
	(*col)++;
	if (((input[*i] == '\"') || input[*i] == '\'') && input[(*i) + 1])
	{
		(*i)++;
		if (input[*i]) //  echo "$HOME$"$"youssef"    input[*i] = '\0'  او هدي *i++ حيت هدي نزيد ب
		{
			handel->a = *i;
			if (input[handel->a] == '\"')
				handel->quote_count = 1;
			else if (input[handel->a] == '\'')
				handel->q = 1;
			else if ((input[*i] != ' ' || input[*i] == '\t') && input[*i] != '>'
				&& input[*i] != '<' && input[*i] != '|' && input[*i])
			{
				(*i)++;
				(*col)++;
				handel->quote_count = 1;
				handel->q = 1;
				handel->a = *i;
			}
		}
	}
	else
		handel->a = ++(*i);
}

int	handel_qoutation1(char *input, int *i, t_handel *handel, int *col)
{
	if (input[handel->a] == '\"' && input[*i] == '\"')
		(handel->quote_count)++;
	if (input[handel->a] == '\'' && input[*i] == '\'')
		(handel->q)++;
	while ((handel->quote_count % 2 == 0 && input[handel->a] == '\"')
		|| (handel->q % 2 == 0 && input[handel->a] == '\''))
	{
		if (*i != handel->a && ((input[*i] == '\"' && input[handel->a] == '\"')
				|| (input[*i] == '\'' && input[handel->a] == '\'')))
		{
			break ;
		}
		(*i)++;
		(*col)++;
		if (!input[*i])// break; دشي علاش مع توصل \0 دير "ls d""skfjfe حيت هدي تبقى تقرى لا م نهاية فية حالة كان
		{
			printf("eroor\n");
			return (0);
		}
	}
	return (1);
}

int	ft_ft1(char *input, int *i, t_handel *handel, int *col)
{
	handel->a = *i;
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
	t_handel	*handel;
	int			col;

	col = 0;
	handel = helper_variables();
	while (input[i] && (input[i] != ' ' && input[i] != '\t')
		&& input[i] != '|' && input[i] != '>' && input[i] != '<')
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (ft_ft1(input, &i, handel, &col) == 0)
				return (0);
		}
		else
		{
			col++;
			i++;
		}
		if (input[i - 1] == '\0' || input[i - 1] == ' '
			|| input[i - 1] == '\t')
			break ;
	}
	return (col);
}
