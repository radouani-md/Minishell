/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_types_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:40:09 by rd_md_haker       #+#    #+#             */
/*   Updated: 2025/06/02 12:55:25 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int implement_outfile(t_node *nodes, t_err *err)
{
	int fd;

	fd = open(nodes->data, O_RDONLY);
	if (fd == -1)
		return (perror("fd "), err->err_status = 1, 3);
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
		if (ft_strcmp(cmd, "unset") == 0)
			return (1);
	}
	return (0);
}

int	countinue_exec_builtin_2(char **cmd, t_env **my_env, t_node **nodes, t_err *err)
{
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		if (!cmd[1])
			implement_env(*my_env);
		else
		{
			printf("env: ‘%s’: No such file or directory\n", cmd[1]);
			err->err_status = 127;
		}
		return (3);
	}
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		if (implement_exit(*my_env, *nodes, err) == 1)
		return (3);
	}
	return (0);
}
int	countinue_exec_builtin(char **cmd, t_env **my_env, t_node **nodes, t_err *err)
{				
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (implement_cd(my_env, *nodes, err) == 1)
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
	return (0);
}

void	saving_fds(int saved_fd_in, int saved_fd_out)
{
	dup2(saved_fd_in, STDIN_FILENO);
	dup2(saved_fd_out, STDOUT_FILENO);
	close(saved_fd_in);
	close(saved_fd_out);
}

int exec_builtin(char **cmd, t_env **my_env, t_node **nodes, t_err *err)
{
	int saved_fd_in;
	int saved_fd_out;
	int her;

	saved_fd_in = dup(STDIN_FILENO);
	saved_fd_out = dup(STDOUT_FILENO);
	her = loop_through_node_builtin(*nodes, *my_env, err);
	if (her == 1)
		return (1);
	else if (her == 3)
		return (3);
	if (countinue_exec_builtin(cmd, my_env, nodes, err) == 1)
		return (1);
	if (countinue_exec_builtin_2(cmd, my_env, nodes, err) == 3)
		return (0);
	if (ft_strcmp(cmd[0], "export") == 0)
	    implement_export(*my_env, *nodes);
	if (ft_strcmp(cmd[0], "unset") == 0)
		implement_unset(my_env, *nodes);
	return (saving_fds(saved_fd_in, saved_fd_out), 0);
}
