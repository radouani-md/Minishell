/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:25:00 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/22 23:22:42 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*yl_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	yl_strlen(char *s, int *i)
{
	size_t	a;

	a = 0;
	if (!*s)
		return (0);
	while (s[*i])
	{
		(*i)++;
		a++;
	}
	return (a);
}

t_env	*ft_lstnew_env(void)
{
	t_env	*new_node;

	new_node = gc_malloc(sizeof(t_env), 1);
	if (!new_node)
		return (NULL);
	new_node->type = 1;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new_node)
{
	t_env	*temp;

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

t_env	*ft_lstnewt(char *env_key, char	*env_value)
{
	t_env	*ptr;

	ptr = (t_env *) gc_malloc(sizeof(t_env), 1);
	if (!ptr)
		return (NULL);
	ptr->value = env_value;
	ptr->key = env_key;
	ptr->type = 1;
	ptr->next = NULL;
	return (ptr);
}
