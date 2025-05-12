/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:43:25 by mradouan          #+#    #+#             */
/*   Updated: 2025/05/12 17:53:38 by mradouan         ###   ########.fr       */
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
	free(trimmed);
	return (0);
}

int	is_valid_n(char *str)
{
	int i;

	if (!str || str[0] != '-')
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
		if (head->data[0] == '$')
		{
			if (helper_echo(env, head->data) == 1)
				return (1);
		}
		else
			ft_putstr(head->data); //ft_printf
		if (head->next && head->next->type == 0) // ft_printf
			ft_putstr(" ");
		head = head->next;
	}
	if (newline)
		ft_putstr("\n");
	return (0);
}

void	implement_exit(t_env **my_env, t_node **nodes)
{
	ft_free2(my_env);
	ft_free1(nodes);
	exit(0);
}
