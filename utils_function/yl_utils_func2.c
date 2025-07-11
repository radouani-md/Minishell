/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:24:54 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/22 20:43:29 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

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

t_list	*ft_lstnew(char *content)
{
	t_list	*new_node;

	new_node = gc_malloc(sizeof(t_list), 1);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

size_t	ft_strlcpy(char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			if (src[i] == '=')
				break ;
			i++;
		}
	}
	return (i);
}

size_t	md_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_strlen(int a, char *dap)
{
	int	t;
	int	len;

	len = 0;
	t = 0;
	while (t < a)
	{
		if (dap[t] == '\"')
			len++;
		t++;
	}
	return (len);
}
