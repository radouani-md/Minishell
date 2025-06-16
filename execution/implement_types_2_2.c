/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_types_2_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:09:33 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/16 18:07:28 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	saving_fds(int saved_fd_in, int saved_fd_out)
{
	dup2(saved_fd_in, STDIN_FILENO);
	dup2(saved_fd_out, STDOUT_FILENO);
	close(saved_fd_in);
	close(saved_fd_out);
}

int	env_implement(char **cmd, t_env **my_env, t_ha *err)
{
	int		i;

	i = 1;
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		while (cmd[i])
		{
			if (ft_strcmp(cmd[i], "env") != 0)
			{
				write(2, "Too many arguments !\n", 21);
				err->err_status = 127;
				return (3);
			}
			i++;
		}
		implement_env(*my_env);
		return (3);
	}
	return (0);
}

int	countinue_exec_builtin_2(char **cmd, t_env **my_env, t_node **nodes,
	t_ha *err)
{
	if (env_implement(cmd, my_env, err) == 3)
		return (3);
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		if (implement_exit(*nodes, err) == 1)
			return (3);
	}
	return (0);
}

int	countinue_exec_builtin(char **cmd, t_env **my_env, t_node **nodes,
	t_ha *err)
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
		if (implement_echo(*nodes) == 1)
			return (1);
	}
	return (0);
}

int	exec_builtin(char **cmd, t_env **my_env, t_node **nodes, t_ha *err)
{
	int	her;

	err->saved_fd_in = dup(STDIN_FILENO);
	err->saved_fd_out = dup(STDOUT_FILENO);
	her = loop_through_node_builtin(*nodes, err);
	if (her == 1)
		return (saving_fds(err->saved_fd_in, err->saved_fd_out),
			close(err->saved_fd_in), close(err->saved_fd_out), 1);
	else if (her == 3)
		return (saving_fds(err->saved_fd_in, err->saved_fd_out),
			close(err->saved_fd_in), close(err->saved_fd_out), 3);
	if (countinue_exec_builtin(cmd, my_env, nodes, err) == 1)
		return (saving_fds(err->saved_fd_in, err->saved_fd_out),
			close(err->saved_fd_in), close(err->saved_fd_out), 1);
	if (countinue_exec_builtin_2(cmd, my_env, nodes, err) == 3)
		return (saving_fds(err->saved_fd_in, err->saved_fd_out),
			close(err->saved_fd_in), close(err->saved_fd_out), 0);
	if (ft_strcmp(cmd[0], "export") == 0)
		implement_export(*my_env, *nodes, err);
	if (ft_strcmp(cmd[0], "unset") == 0)
		implement_unset(my_env, *nodes);
	return (saving_fds(err->saved_fd_in, err->saved_fd_out),
		close(err->saved_fd_in), close(err->saved_fd_out), 0);
}
