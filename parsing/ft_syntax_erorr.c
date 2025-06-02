/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_erorr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:10:26 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/01 22:14:17 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tchik_pipe(t_list *lst)
{
	if (lst->content[0] == '|')
		return (1);
	else if ((lst->content[0] == '<' || lst->content[0] == '>')
		&& (lst->next == NULL))
	{
		return (1);
	}
	else if ((lst->content[0] == '<' || lst->content[0] == '>')
		&& (lst->next->content[0] == '|' || lst->next->content[0] == '<'
			|| lst->next->content[0] == '>'))
	{
		return (1);
	}
	return (0);
}

void	syntax_erorr(t_list *lst)
{
	if (tchik_pipe(lst))
	{
		printf("bash: syntax error `%c'\n", lst->content[0]);
		gc_malloc(0, 0);
		exit(1);
	}
	else
	{
		while (lst->next)
		{
			if ((lst->content[0] == '<' || lst->content[0] == '>')
				&& (lst->next->content[0] == '|' || lst->next->content[0] == '<'
					|| lst->next->content[0] == '>'))
				return (printf("bash: syntax error `%s'\n",
						lst->next->content), gc_malloc(0, 0), exit(1));
			else if ((lst->content[0] == '|') && (lst->next->content[0] == '|'))
				return (printf("bash: syntax error `|'\n"),
					gc_malloc(0, 0), exit(1));
			lst = lst->next;
			if (lst->next == NULL && (lst->content[0] == '|'
					|| lst->content[0] == '<' || lst->content[0] == '>'))
				return (printf("bash: syntax error `newline'\n"),
					gc_malloc(0, 0), exit(1));
		}
	}
}
