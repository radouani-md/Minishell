/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_and_filling_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:17:33 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/01 22:41:58 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handel_pipe_direction(char *input, int *i, t_list **lst)
{
	char	*temp;
	int		n;
	int		a;

	a = 0;
	n = *i;
	if ((input[n] == '>' && input[n + 1] == '>')
		|| (input[n] == '<' && input[n + 1] == '<'))
		temp = gc_malloc(3, 1);
	else
		temp = gc_malloc(2, 1);
	a = 0;
	temp[a++] = input[*i];
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
		temp[a++] = input[++(*i)];
	temp[a] = '\0';
	ft_lstadd_back(lst, ft_lstnew(temp));
	(*i)++;
}

void	ft_handle_double_single(char *input, int *i, t_list **lst)
{
	t_handel	*handel;

	handel = helper_variables();
	handel->temp = gc_malloc(count_string(input, *i, handel) + 1, 1);
	handel->a = *i;
	while (input[*i])
	{
		handel_qoutation(input, i, handel);
		handle_multiple_quotes(input, i, handel);
		if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
		{
			break ;
		}
	}
	handel->temp[handel->t] = '\0';
	ft_lstadd_back(lst, ft_lstnew(handel->temp));
}

void	ft_ft(char *input, int *i, t_handel *handel)
{
	handel->a = *i;
	while (input[*i])
	{
		handel_qoutation(input, i, handel);
		handle_multiple_quotes(input, i, handel);
		if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '|'
				|| input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
			break ;
	}
}

void	ft_handle_string(char	*input, int	*i, t_list	**lst)
{
	t_handel	*handel;

	handel = helper_variables();
	handel->temp = gc_malloc(count_handle_str(input, *i) + 1, 1);
	while (input[*i] && (input[*i] != ' ' && input[*i] != '\t')
		&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
	{
		if (input[*i] == '\"' || input[*i] == '\'')
		{
			ft_ft(input, i, handel);
		}
		else
			handel->temp[(handel->t)++] = input[(*i)++];
		if (input[*i - 1] == '\0' || input[*i - 1] == ' '
			|| input[*i - 1] == '\t')
			break ;
	}
	handel->temp[handel->t] = '\0';
	ft_lstadd_back(lst, ft_lstnew(handel->temp));
}

void	read_and_filling_node(char *input, t_list **lst)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] != ' ' && input[i] != '\t')
		{
			if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			{
				ft_handel_pipe_direction(input, &i, lst);
			}
			else if (input[i] == '\"' || input[i] == '\'')
			{
				ft_handle_double_single(input, &i, lst);
			}
			else
			{
				ft_handle_string(input, &i, lst);
			}
		}
		if (input[i] == ' ' || input[i] == '\t')
			i++;
	}
}
