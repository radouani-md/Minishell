/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_types_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:40:09 by rd_md_haker       #+#    #+#             */
/*   Updated: 2025/05/26 16:33:36 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void safe_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int implement_outfile(t_node *nodes)
{
	int fd;

	fd = open(nodes->data, O_RDONLY);
	if (fd == -1)
		return (perror("fd "), 1);
	return (0);
}

int is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "env") == 0)
			return (1);
		if (ft_strcmp(cmd, "cd") == 0)
			return (1);
		if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		if (ft_strcmp(cmd, "export") == 0)
			return (1);
		if (ft_strcmp(cmd, "echo") == 0)
			return (1);
		if (ft_strcmp(cmd, "exit") == 0)
			return (1);
	}
	return (0);
}

int exec_builtin(char **cmd, t_env **my_env, t_node **nodes)
{
	int saved_fd_in;
	int saved_fd_out;

	saved_fd_in = dup(STDIN_FILENO);
	saved_fd_out = dup(STDOUT_FILENO);
	if (loop_through_node_builtin(*nodes, *my_env) == 1)
		return (1);
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		implement_env(*my_env);
		return (0);
	}				
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (implement_cd(my_env, *nodes) == 1)
			return (1);
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		if (implement_pwd(*my_env) == 1)
			return (1);
	}
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		if (implement_echo(*my_env, *nodes) == 1)
			return (1);
	}
	if (ft_strcmp(cmd[0], "exit") == 0)
		implement_exit(my_env, nodes);
	
	if (ft_strcmp(cmd[0], "export") == 0)
	{
	    if (implement_export(*my_env, *nodes) == 0)
	        return (1);
	}
	dup2(saved_fd_in, STDIN_FILENO);
	dup2(saved_fd_out, STDOUT_FILENO);
	close(saved_fd_in);
	close(saved_fd_out);
	return (0);
}
