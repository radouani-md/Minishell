/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_work_of_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:07:29 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/10 19:56:49 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **load_env(t_env *my_env)
{
	t_env *tmp;
	char	*joined;
	char **enverment;
	int i;

	i = 0;
	tmp = my_env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	enverment = gc_malloc(sizeof(char *) * (i + 1), 1);
	if (!enverment)
		return (perror("malloc "), NULL);
	i = 0;
	while (my_env)
	{
		joined = md_strjoin(my_env->key, "=");
		enverment[i] = md_strjoin(joined, my_env->value);
		my_env = my_env->next;
		i++;
	}
	enverment[i] = NULL;
	return (enverment);
}

void	catch_signals(t_ha *err, pid_t pid)
{
	int status;
	pid_t wpid;
	
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == pid)
		{
			if (WIFEXITED(status))
				err->err_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				err->err_status = 128 + WTERMSIG(status);
		}
	}
}

int	spliting_nodes_hd(t_md *md, t_node *nodes, t_env *my_env, t_ha *err)
{
	if (implement_her_doc(nodes, my_env, err) == -333)
	{
		return (-333);
	}
	md->groups = split_nodes_by_pipe(nodes, &md->num_groups);
	if (!md->groups)
	{
		gc_malloc(0, 0);
		exit(1);
	}
	return (0);
}

int set_md(t_md **md, t_node *nodes, t_env *my_env, t_ha *err)
{
	*md = gc_malloc(sizeof(t_md), 1);
	(*md)->prev_fd = -1;
	(*md)->i = 0;
	(*md)->pid = 0;
	if (spliting_nodes_hd(*md, nodes, my_env, err) == -333)
		return (-333);
	return (0);
}

void	parent_work(t_md *md)
{
	if (md->prev_fd != -1)
		close(md->prev_fd);
	close(md->pip_fd[1]);
	md->prev_fd = md->pip_fd[0];
	md->pid = md->id;
	md->i++;
}

int	forking_pip(t_md *md, t_env **my_env, t_ha *err, t_node *nodes)
{
	int her;
	if (md->prev_fd != -1)
	{
		dup2(md->prev_fd, STDIN_FILENO);
		close(md->prev_fd);
	}
	if (md->i + 1 < md->num_groups)
		dup2(md->pip_fd[1], STDOUT_FILENO);
	close(md->pip_fd[1]);
	close(md->pip_fd[0]);
	her = loop_through_node_builtin(nodes, *my_env, err);
	if (her == 1)
		exit(1);
	else if (her == 3)
		return (3);
	md->cmd = helper_loop(md->cmd, md->groups[md->i]);
	if (!md->cmd)
		exit(1);
	md->cmd_path = is_accessable(fetch_path(*my_env), md->cmd[0]);
	if (!md->cmd_path || !*md->cmd[0])
	{
		ft_printf("mhd %s: command not found\n", md->cmd[0]);
		exit(127);
	}
	if (!*md->cmd)
		exit(127);
	execve(md->cmd_path, md->cmd, load_env(*my_env));
	perror("execeve (cmd2)");
	exit(127);
}

void	helper_built(t_md *md, t_ha *err)
{
	md->cmd2 = loop_through_node_cmd(md->groups[md->i]);
	if (!md->cmd2)
	{
		gc_malloc(0, 0);
		exit(127);
	}
	err->err_status = 0;
}

int	piping_forking(t_node **nodes, t_env **my_env, t_ha *err)
{
	t_md	*md;

	md = NULL;
	if (set_md(&md, *nodes, *my_env, err) == -333)
		return (-333);
	while (md->i < md->num_groups)
	{
		helper_built(md, err);
		if (is_builtin(md->cmd2[0]) && md->num_groups == 1)
		{
			if (exec_builtin(md->cmd2, my_env, nodes, err) == 1)
				exit(1);
			md->i++;
			continue ;
		}
		if (pipe(md->pip_fd) == -1)
			return (-1);
		g_sig_md = 2;
		md->id = fork();
		if (md->id == -1)
			return (-1);
		if (md->id == 0)
		{
			if (forking_pip(md, my_env, err, *nodes) == 3)
			{
				md->i++;
				exit(0);
			}
		}
		else
			parent_work(md);
	}
	return (catch_signals(err, md->pid), 0);
}
