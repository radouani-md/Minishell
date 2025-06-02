/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:43:25 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/02 10:57:25 by mradouan         ###   ########.fr       */
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
		return (perror("malloc "), 1);
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
	return (0);
}

int	is_valid_n(char *str)
{
	int i;

	if (!str || ft_strncmp(str, "-n", 2) != 0)
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_newline_flag(t_node **nodes)
{
	int	newline;

	newline = 1;

	while (*nodes && is_valid_n((*nodes)->data))
	{
		newline = 0;
		*nodes = (*nodes)->next;
	}
	return (newline);
}

int	implement_echo(t_env *env, t_node *nodes)
{
	int	newline;
	t_node	*head;

	head = nodes;
	while (head && ft_strcmp(head->data, "echo") != 0)
		head = head->next;
	if (!head || !head->next)
		return (ft_putstr("\n"), 0);
	head = head->next;
	newline = check_newline_flag(&head);
	while (head && head->type == 0)
	{
		ft_putstr(head->data); //ft_printf
		if (head->next && head->next->type == 0) // ft_printf
			ft_putstr(" ");
		head = head->next;
	}
	if (newline)
		ft_putstr("\n");
	return (0);
}

int	implement_exit(t_env *my_env, t_node *nodes, t_err *err)
{
	if (nodes->next && nodes->next->next)
		return (printf("exit\nminishell: exit: too many arguments\n"), 1);
	else if (nodes && nodes->next)
	{
		printf("exit\n");
		gc_malloc(0, 0);
		exit(37); //nodes->next->data
	}
	printf("exit\n");
	gc_malloc(0, 0);
	exit(1);
}
