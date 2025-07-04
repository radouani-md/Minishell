/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:25:06 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/22 23:21:51 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*last;

	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_lstadd_back12(t_env **lst, t_env *new)
{
	t_env	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	ft_lstadd_back1(t_node **lst, t_node *new_node)
{
	t_node	*temp;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_node	*ft_lstnew1(char *content, int type)
{
	t_node	*new_node;

	new_node = gc_malloc(sizeof(t_node), 1);
	new_node->data = content;
	new_node->type = type;
	new_node->back_type = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*ft_lstnew2(char *content, int type, char *tmp_file, int heredoc_fd)
{
	t_node	*new_node;

	new_node = gc_malloc(sizeof(t_node), 1);
	new_node->data = content;
	new_node->type = type;
	new_node->heredoc_fd = heredoc_fd;
	new_node->tmp_file = tmp_file;
	new_node->next = NULL;
	return (new_node);
}
