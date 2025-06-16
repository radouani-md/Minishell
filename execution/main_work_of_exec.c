/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_work_of_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:07:29 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/16 19:05:41 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**load_env(t_env *my_env)
{
	t_env	*tmp;
	char	*joined;
	char	**enverment;
	int		i;

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
		close(err->saved_fd);
		exit(1);
	}
	return (0);
}

int	forking(t_md *md, t_ha *err, t_env **my_env)
{
	if (md->id == -1)
		return (-1);
	if (md->id == 0)
	{
		if (child_work(md, my_env, err) == 3)
		{
			md->i++;
			gc_malloc(0, 0);
			exit(1);
		}
	}
	else
		parent_work(md);
	return (0);
}

int	built_fork_work(t_md *md, t_ha *err, t_env **my_env)
{
	while (md->i < md->num_groups)
	{
		helper_built(md, err);
		if (is_builtin(md->cmd2[0]) && md->num_groups == 1)
		{
			if (exec_builtin(md->cmd2, my_env, &md->groups[md->i], err) == 1)
			{
				close(err->saved_fd);
				gc_malloc(0, 0);
				exit(1);
			}
			md->i++;
			continue ;
		}
		if (pipe(md->pip_fd) == -1)
			return (-1);
		g_sig_md = 2;
		md->id = fork();
		if (forking(md, err, my_env) == -1)
			return (-1);
	}
	return (0);
}

int	piping_forking(t_node **nodes, t_env **my_env, t_ha *err)
{
	t_md	*md;

	md = NULL;
	if (set_md(&md, *nodes, *my_env, err) == -333)
		return (-333);
	if (built_fork_work(md, err, my_env) == -1)
		return (-1);
	if (md->prev_fd != -1)
		close(md->prev_fd);
	return (catch_signals(err, md->pid), 0);
}
