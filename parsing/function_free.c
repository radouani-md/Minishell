/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:20:28 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/09 21:21:22 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

void	ft_free1(t_node **arg)
{
	t_node	*temp;

	while (*arg)
	{
		temp = (*arg)->next;
		free((*arg)->data);
		free(*arg);
		*arg = temp;
	}
}

void	ft_free2(t_env **my_envp)
{
	t_env	*temp;

	while (*my_envp)
	{
		temp = (*my_envp)->next;
		free((*my_envp)->key);
		free((*my_envp)->value);
		*my_envp = temp;
	}
}

void	md_free_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_group(t_node *group)
{
	t_node	*tmp;

	while (group)
	{
		tmp = group->next;
		if (group->data)
			free(group->data);
		free(group);
		group = tmp;
	}
}
