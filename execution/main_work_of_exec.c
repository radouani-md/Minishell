/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_work_of_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:07:29 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/02 18:29:50 by mradouan         ###   ########.fr       */
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

void	catch_signals(t_err *err, pid_t pid)
{
	int status;
	pid_t wpid;
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == pid)
		{
			if (WIFEXITED(status))
			err->err_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
			err->err_status = 128 + WTERMSIG(status);
	}
}

void	spliting_nodes_hd(t_md *md, t_node *nodes, t_env *my_env, t_err *err)
{
	if (implement_her_doc(nodes, my_env, err) == 1)
	{
		gc_malloc(0, 0);
		exit(1);
	}
	md->groups = split_nodes_by_pipe(nodes, &md->num_groups);
	if (!md->groups)
	{
		gc_malloc(0, 0);
		exit(1);
	}
}

void set_md(t_md **md, t_node *nodes, t_env *my_env, t_err *err)
{
	*md = gc_malloc(sizeof(t_md), 1);
	(*md)->prev_fd = -1;
	(*md)->i = 0;
	(*md)->pid = 0;
	spliting_nodes_hd(*md, nodes, my_env, err);
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

void	forking_pip(t_md *md, t_env **my_env, t_err *err)
{
	if (md->prev_fd != -1)
	{
		dup2(md->prev_fd, STDIN_FILENO);
		close(md->prev_fd);
	}
	if (md->i + 1 < md->num_groups)
		dup2(md->pip_fd[1], STDOUT_FILENO);
	close(md->pip_fd[1]);
	close(md->pip_fd[0]);
	md->cmd = loop_through_node(md->groups[md->i], NULL, *my_env, err);
	if (!md->cmd)
		exit(1);
	md->cmd_path = is_accessable(fetch_path(*my_env), md->cmd[0]);
	if (!md->cmd_path)
	{
		printf("mhd %s: command not found\n", md->cmd[0]);
		exit(127);
	}
	if (!*md->cmd)
		exit(127);
	execve(md->cmd_path, md->cmd, load_env(*my_env));
	perror("execeve (cmd2)");
	exit(127);
}

void	helper_built(t_md *md, t_err *err)
{
	md->cmd2 = loop_through_node_cmd(md->groups[md->i]);
	if (!md->cmd2)
	{
		gc_malloc(0, 0);
		exit(127);
	}
	err->err_status = 0;
}

int	piping_forking(t_node **nodes, t_env **my_env, t_err *err)
{
	t_md	*md;

	md = NULL;
	set_md(&md, *nodes, *my_env, err);
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
		md->id = fork();
		if (md->id == -1)
			return (-1);
		if (md->id == 0)
			forking_pip(md, my_env, err);
		else
			parent_work(md);
	}
	return (catch_signals(err, md->pid), 0);
}
