/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:01:57 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/10 20:01:07 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_node(t_env **env_node)
{
	if (env_node == NULL || *env_node == NULL)
		return ;
	*env_node = (*env_node)->next;
}

int	implement_unset(t_env **my_env, t_node *nodes)
{
	t_env	**cpy_env;

	nodes = nodes->next;
	while (nodes)
	{
		cpy_env = my_env;
		while (*cpy_env)
		{
			if (!ft_strcmp((*cpy_env)->key, nodes->data))//ft_cpy_key(i, nodes)
			{
				delete_node(cpy_env);
				printf("hi\n");
				break ;
			}
			*cpy_env = (*cpy_env)->next;
		}
		nodes = nodes->next;
	}
	return (0);
}
