/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_type_2_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:51:13 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/21 19:53:05 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countinue_exec_builtin_child(char **cmd, t_env **my_env, t_node **nodes,
	t_ha *err)
{				
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (implement_cd_child(my_env, *nodes, err) == 1)
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

int	exec_builtin_child(char **cmd, t_env **my_env, t_node **nodes, t_ha *err)
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
	if (countinue_exec_builtin_child(cmd, my_env, nodes, err) == 1)
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
