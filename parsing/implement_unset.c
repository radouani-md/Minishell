/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:01:57 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/16 11:35:51 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	implement_unset(t_env **my_env, t_node *nodes)
{
	t_env	*cpy_env;
	t_env	*back;

	nodes = nodes->next;
	while (nodes)
	{
		cpy_env = *my_env;
		back = NULL;
		while (cpy_env)
		{
			if (!ft_strcmp((cpy_env)->key, nodes->data)
				&& ft_strcmp(nodes->data, "_"))
			{
				if (back == NULL)
					*my_env = cpy_env->next;
				else
					back->next = cpy_env->next;
				break ;
			}
			back = cpy_env;
			cpy_env = cpy_env->next;
		}
		nodes = nodes->next;
	}
	return (0);
}
