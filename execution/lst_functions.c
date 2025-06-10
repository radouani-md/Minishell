/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:49:42 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/10 09:58:44 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// t_node	*ft_lstneww(char *lst, int typ_e)
// {
// 	t_node	*ptr;

// 	ptr = (t_node *) malloc(sizeof(t_node));
// 	if (!ptr)
// 		return (NULL);
// 	ptr->data = lst;
// 	ptr->type = typ_e;
// 	ptr->next = NULL;
// 	return (ptr);
// }


// t_cmds	*ft_lstlas(t_cmds *lst)
// {
// 	t_cmds	*last;

// 	last = lst;
// 	while (last->next)
// 		last = last->next;
// 	return (last);
// }

// t_node	*ft_lstlastt(t_node *lst)
// {
// 	t_node	*last;

// 	last = lst;
// 	while (last->next)
// 		last = last->next;
// 	return (last);
// }

// void	ft_lstadd_back_m(t_env **lst, t_env *new)
// {
// 	t_env	*last;

// 	if (new == NULL)
// 	return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		last = ft_lstlast(*lst);
// 		last->next = new;
// 	}
// }

// void	ft_lstadd_bck(t_cmds **lst, t_cmds *new)
// {
// 	t_cmds	*last;

// 	if (new == NULL)
// 	return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		last = ft_lstlas(*lst);
// 		last->next = new;
// 	}
// }

// void	ft_lstadd_backk(t_node **lst, t_node *new)
// {
// 	t_node	*last;

// 	if (new == NULL)
// 	return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		last = ft_lstlastt(*lst);
// 		last->next = new;
// 	}
// }

// void	ft_lstadd_front(t_env **lst, t_env *new)
// {
// 	if (new == NULL)
// 		return ;
// 	new->next = *lst;
// 	*lst = new;
// }


void	md_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

void	alloc_arm(t_var	**arm)
{
	*arm = gc_malloc(sizeof(t_var), 1);
	(*arm)->in_var = 0;
	(*arm)->out_var = 0;
	(*arm)->append_var = 0;
}
