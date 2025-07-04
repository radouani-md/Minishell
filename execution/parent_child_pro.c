/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_pro.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:30:36 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/24 14:34:17 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_work(t_md *md, t_ha *err)
{
	(void)err;
	if (md->prev_fd != -1)
		close(md->prev_fd);
	md->prev_fd = md->pip_fd[0];
	close(md->pip_fd[1]);
	md->pid = md->id;
	md->i++;
}

void	execve_cmd(t_md *md, t_env *my_env)
{
	execve(md->cmd_path, md->cmd, load_env(my_env));
	ft_print_erorr("minishell: ", md->cmd_path, ": Execution error\n", NULL);
	gc_malloc(0, 0);
	exit(127);
}

void	child_work_helper2(t_md *md, t_env *my_env, t_ha *err)
{
	int	err_code;

	err_code = 0;
	check_cmd(md, err);
	md->cmd_path = is_accessable(fetch_path(my_env), md->cmd[0]);
	if (!md->cmd_path || (md->cmd[0] && !*md->cmd[0]))
	{
		ft_print_erorr("mhd: ", md->cmd[0], ": command not found", "\n");
		close(err->saved_fd);
		gc_malloc(0, 0);
		exit(127);
	}
	if (!*md->cmd)
	{
		gc_malloc(0, 0);
		exit(0);
	}
	err_code = check_exec_errors(md->cmd_path);
	if (err_code != 0)
	{
		gc_malloc(0, 0);
		exit(err_code);
	}
	execve_cmd(md, my_env);
}

void	child_work_helper(t_md *md, t_env **my_env, t_ha *err)
{
	if (is_builtin(md->cmd[0]))
	{
		if (exec_builtin_child(md->cmd, my_env, &md->groups[md->i], err) == 1)
		{
			close(err->saved_fd);
			gc_malloc(0, 0);
			exit(1);
		}
		close(err->saved_fd);
		gc_malloc(0, 0);
		exit(0);
	}
	if (!md->cmd || !md->cmd[0])
	{
		close(err->saved_fd);
		gc_malloc(0, 0);
		exit(0);
	}
	child_work_helper2(md, *my_env, err);
}

int	child_work(t_md *md, t_env **my_env, t_ha *err)
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
	her = loop_through_node_builtin(md->groups[md->i], err);
	if (her == 1)
	{
		close(err->saved_fd);
		gc_malloc(0, 0);
		exit(1);
	}
	else if (her == 3)
		return (close(err->saved_fd), 3);
	child_work_helper(md, my_env, err);
	return (0);
}
