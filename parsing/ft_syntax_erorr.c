/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_erorr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:10:26 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/12 02:04:08 by ylagzoul         ###   ########.fr       */
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

void	ft_print_erorr(char *str1, char *str2, char *str3, char *str4)
{
	char	*str_print;

	str_print = NULL;
	str_print = md_strjoin(str_print, str1);
	str_print = md_strjoin(str_print, str2);
	str_print = md_strjoin(str_print, str3);
	str_print = md_strjoin(str_print, str4);
	write(2, str_print, md_strlen(str_print));
}

int	syntax_erorr(t_list *lst)
{
	if (tchik_pipe(lst))
	{
		ft_print_erorr("bash: syntax error1 `", "|", "'\n", NULL);
		//lst->content[0]
		return (0);
	}
	else
	{
		while (lst->next)
		{
			if ((lst->content[0] == '<' || lst->content[0] == '>')
				&& (lst->next->content[0] == '|' || lst->next->content[0] == '<'
					|| lst->next->content[0] == '>'))
				return (ft_print_erorr("bash: syntax error `",
						lst->next->content, "'\n", NULL), 0);
			else if ((lst->content[0] == '|') && (lst->next->content[0] == '|'))
				return (write(2, "bash: syntax error `|'\n", 23), 0);
			lst = lst->next;
			if (lst->next == NULL && (lst->content[0] == '|'
					|| lst->content[0] == '<' || lst->content[0] == '>'))
				return (write(2, "bash: syntax error `newline'\n", 29), 0);
		}
	}
	return (1);
}
