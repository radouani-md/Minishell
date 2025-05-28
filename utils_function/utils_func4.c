/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:02:18 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/28 10:47:42 by mradouan         ###   ########.fr       */
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

t_node	*ft_lstnew5()
{
    t_node	*new_node;

	new_node = malloc(sizeof(t_node));
    if (!new_node)
        return (NULL);

    new_node->data = NULL;
    new_node->next = NULL;
    return (new_node);
}

void ft_lstadd_back1(t_node **lst, t_node *new_node)
{
    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    t_node *temp = *lst;
    while (temp->next)
        temp = temp->next;

    temp->next = new_node;
}

t_node *ft_lstnew1(char *content, int type)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->data = md_strdup(content);
    new_node->type = type;
    new_node->next = NULL;
    return new_node;
}

t_node *ft_lstnew2(char *content, int type, char *tmp_file)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->data = md_strdup(content);
    new_node->type = type;
    new_node->tmp_file = tmp_file;
    new_node->next = NULL;
    return new_node;
}
