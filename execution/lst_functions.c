/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:49:42 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/13 13:12:04 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *env_key, char *env_value)
{
	t_env	*ptr;

	ptr = (t_env *) malloc(sizeof(t_env));
	if (!ptr)
		return (NULL);
	ptr->value = env_value;
    ptr->key = env_key;
	ptr->next = NULL;
	return (ptr);
}

// t_cmds	*ft_lstnw(char *command)
// {
// 	t_cmds	*ptr;

// 	ptr = (t_cmds *) malloc(sizeof(t_cmds));
// 	if (!ptr)
// 		return (NULL);
// 	ptr->cmd = command;
// 	ptr->next = NULL;
// 	return (ptr);
// }

t_list	*ft_lstneww(char *lst, int typ_e)
{
	t_list	*ptr;

	ptr = (t_list *) malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->data = lst;
	ptr->type = typ_e;
	ptr->next = NULL;
	return (ptr);
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*last;

	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

// t_cmds	*ft_lstlas(t_cmds *lst)
// {
// 	t_cmds	*last;

// 	last = lst;
// 	while (last->next)
// 		last = last->next;
// 	return (last);
// }

t_list	*ft_lstlastt(t_list *lst)
{
	t_list	*last;

	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

t_env	*ft_lstlast_befor(t_env *lst)
{
	t_env	*last;

	last = lst;
	while (last->next->next)
		last = last->next;
	return (last);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
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

void	ft_lstadd_backk(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
	return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlastt(*lst);
		last->next = new;
	}
}

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
