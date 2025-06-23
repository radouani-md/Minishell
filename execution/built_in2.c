/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:43:25 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/23 12:53:23 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper_echo(t_env *env, char *nodes_data)
{
	t_env	*head;
	char	*trimmed;

	head = env;
	trimmed = md_strtrim(nodes_data, "$");
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
	int	i;

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

int	implement_echo(t_node *nodes)
{
	int		newline;

	while (nodes && ft_strcmp(nodes->data, "echo") != 0)
		nodes = nodes->next;
	if (!nodes->next)
		return (printf("\n"), 0);
	nodes = nodes->next;
	newline = check_newline_flag(&nodes);
	while (nodes && nodes->type == 0)
	{
		md_putstr(nodes->data);
		if (nodes->next && nodes->next->type == 0)
			md_putstr(" ");
		nodes = nodes->next;
	}
	if (newline)
		md_putstr("\n");
	return (0);
}

int	implement_exit(t_node *nodes, t_ha *err)
{
	long long	exit_state;

	exit_state = 0;
	close(err->saved_fd_in);
	close(err->saved_fd_out);
	close(err->saved_fd);
	if (nodes->next && (md_isalpha(nodes->next->data)
			&& nodes->next->type == 0))
		return (ft_print_erorr("exit\nmhd: exit: ", nodes->next->data,
				": numeric argument required", "\n"),
			gc_malloc(0, 0), exit(2), 1);
	if (nodes->next && nodes->next->next)
		return (write(2, "exit\nminishell: exit: too many arguments\n", 41),
			err->err_status = 1, 1);
	else if (nodes && nodes->next)
	{
		exit_state = md_atoi(nodes->next->data);
		printf("exit\n");
		gc_malloc(0, 0);
		exit(exit_state);
	}
	gc_malloc(0, 0);
	exit(0);
}
