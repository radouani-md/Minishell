/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:43:25 by mradouan          #+#    #+#             */
/*   Updated: 2025/05/03 09:26:36 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper_echo(t_env *env, char *nodes_data)
{
	t_env *head;
	char *trimmed;

	head = env;
	trimmed = md_strtrim(nodes_data, "$");
	if (!trimmed)
		return (1);
	while (env)
	{
		if (ft_strcmp(trimmed, env->key) == 0)
		{
			if (env->value)
				printf("%s", env->value);
			break ;
		}
		env = env->next;
	}
	env = head;
	free(trimmed);
	return (0);
}

int	check_newline_flag(t_node **nodes)
{
	int	newline;

	newline = 1;
	while (*nodes && ft_strcmp((*nodes)->data, "-n") == 0)
	{
		newline = 0;
		*nodes = (*nodes)->next;
	}
	return (newline);
}

int	implement_echo(t_env *env, t_node *nodes)
{
	int	newline;

	while (nodes && ft_strcmp(nodes->data, "echo") != 0)
		nodes = nodes->next;
	if (!nodes || !nodes->next)
		return (printf("\n"), 0);
	nodes = nodes->next;
	newline = check_newline_flag(&nodes);
	while (nodes && nodes->type == 0)
	{
		if (nodes->data[0] == '$')
		{
			if (helper_echo(env, nodes->data) == 1)
				return (1);
		}
		else
			printf("%s", nodes->data);
		if (nodes->next && nodes->next->type == 0)
			printf(" ");
		nodes = nodes->next;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	implement_exit(t_env **my_env, t_node **nodes)
{
	ft_free2(my_env);
	ft_free1(nodes);
	exit(0);
	return (0);
}
