/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_pro.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:30:36 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/13 22:05:10 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_work(t_md *md)
{
	if (md->prev_fd != -1)
		close(md->prev_fd);
	md->prev_fd = md->pip_fd[0];
	close(md->pip_fd[1]);
	md->pid = md->id;
	md->i++;
}

void	child_work_helper(t_md *md, t_env **my_env, t_ha *err)
{
	if (is_builtin(md->cmd[0]))
	{
		if (exec_builtin(md->cmd, my_env, &md->groups[md->i], err) == 1)
			exit(1);
		exit(0);
	}
	if (!md->cmd)
		exit(1);
	md->cmd_path = is_accessable(fetch_path(*my_env), md->cmd[0]);
	if (!md->cmd_path || (md->cmd[0] && !*md->cmd[0]))
	{
		ft_printf("mhd %s: command not found\n", md->cmd[0]);
		exit(127);
	}
	if (!*md->cmd)
		exit(0);
	execve(md->cmd_path, md->cmd, load_env(*my_env));
	exit(126);
}

int	child_work(t_md *md, t_env **my_env, t_ha *err, t_node *nodes)
{
	int	her;

	signal(SIGQUIT, SIG_DFL);
	if (md->prev_fd != -1)
	{
		dup2(md->prev_fd, STDIN_FILENO);
		close(md->prev_fd);
	}
	if (md->i + 1 < md->num_groups)
		dup2(md->pip_fd[1], STDOUT_FILENO);
	close(md->pip_fd[1]);
	close(md->pip_fd[0]);
	md->cmd = helper_loop(md->cmd, md->groups[md->i]);
	her = loop_through_node_builtin(md->groups[md->i], *my_env, err);
	if (her == 1)
		exit(1);
	else if (her == 3)
		return (3);
	child_work_helper(md, my_env, err);
	return (0);
}
