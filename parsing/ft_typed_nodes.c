/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typed_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:22:03 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/18 11:22:05 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*typed_nodes(t_list *lst)
{
	t_node	*arg;

	arg = NULL;
	while (lst)
	{
		if (lst->content[0] == '<' || lst->content[0] == '>')
		{
			if (lst->content[0] == '<' && lst->content[1] == '\0')
				ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content, 1));
			else if (lst->content[0] == '>' && lst->content[1] == '\0')
				ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content, 2));
			else if (lst->content[0] == '<' && lst->content[1] == '<')
				ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content, 3));
			else if (lst->content[0] == '>' && lst->content[1] == '>')
				ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content, 4));
			lst = lst->next;
		}
		else if (lst->content[0] == '|')
			ft_lstadd_back1(&arg, ft_lstnew1(lst->content, 5));
		else
			ft_lstadd_back1(&arg, ft_lstnew1(lst->content, 0));
		lst = lst->next;
	}
	return (arg);
}
