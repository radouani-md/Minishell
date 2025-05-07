/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_work_of_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:07:29 by mradouan          #+#    #+#             */
/*   Updated: 2025/05/06 14:45:58 by mradouan         ###   ########.fr       */
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
	enverment = malloc(sizeof(char *) * (i + 1));
	if (!enverment)
		return (NULL);
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

int	piping_forking(char *cmd_path, char **cmd, t_node **nodes, t_env **my_env)
{
	int pip_fd[2];
	int prev_fd = -1;
	t_node **groups;
	char **cmd2;
	int num_groups;
	int i = 0;
	pid_t	id;
	
	groups = split_nodes_by_pipe(*nodes, &num_groups);
	while (i < num_groups)
	{
		cmd2 = loop_through_node_cmd(groups[i]);
		if (is_builtin(cmd2[0]) && num_groups == 1)
		{
			exec_builtin(cmd2, my_env, nodes);
			md_free_char(cmd2);
			i++;
			continue ;
		}
		if (pipe(pip_fd) == -1)
			return (-1);
		id = fork();
		if (id == -1)
			return (-1);
		if (id == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i + 1 < num_groups)
				dup2(pip_fd[1], STDOUT_FILENO);
			close(pip_fd[1]);
			close(pip_fd[0]);
			cmd = loop_through_node(groups[i], NULL);
			cmd_path = is_accessable(fetch_path(*my_env), cmd[0]);
			if (!cmd_path)
			{
				md_free_char(cmd);
				exit(write(2, "mhd: command not found\n", 24));
			}
			execve(cmd_path, cmd, load_env(*my_env));
			md_free_char(&(*groups)->data);
			perror("execeve (cmd2)");
			exit(1);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			close(pip_fd[1]);
			prev_fd = pip_fd[0];
			i++;
		}
	}
	while (wait(NULL) > 0);
	return (0);
}
