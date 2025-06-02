/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:06:46 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/01 22:08:53 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_malloc(t_malloc **lst, t_malloc *new_node)
{
	t_malloc	*temp;

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

t_malloc	*ft_lstnew_malloc(void *mlc)
{
	t_malloc	*new_node;

	new_node = malloc(sizeof(t_malloc));
	if (!new_node)
		return (exit(1), NULL);
	new_node->data = mlc;
	new_node->next = NULL;
	return (new_node);
}

void	*gc_malloc(size_t size, int nbr)
{
	void			*mlc;
	static t_malloc	*ptr;
	t_malloc		*tmp;

	if (nbr == 1)
	{
		mlc = malloc(size);
		if (!mlc)
			return (exit(1), NULL);
		tmp = ft_lstnew_malloc(mlc);
		ft_lstadd_back_malloc(&ptr, tmp);
	}
	else if (nbr == 0)
	{
		while (ptr)
		{
			tmp = ptr->next;
			free(ptr->data);
			free(ptr);
			ptr = tmp;
		}
		mlc = NULL;
	}
	return (mlc);
}
