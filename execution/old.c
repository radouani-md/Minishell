/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:21:56 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/22 17:16:50 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

// char **load_env(t_env *my_env)
// {
// 	t_env *tmp;
// 	char	*joined;
// 	char **enverment;
// 	int i;

// 	i = 0;
// 	tmp = my_env;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	enverment = malloc(sizeof(char *) * (i + 1));
// 	if (!enverment)
// 		return (NULL);
// 	i = 0;
// 	while (my_env)
// 	{
// 		joined = md_strjoin(my_env->key, "=");
// 		enverment[i] = md_strjoin(joined, my_env->value);
// 		my_env = my_env->next;
// 		i++;
// 	}
// 	enverment[i] = NULL;
// 	return (enverment);
// }

// int	piping_forking(char *cmd_path, char **cmd, char **group_cmd, t_node *nodes, t_env *my_env)
// {
// 	int pip_fd[2];
// 	int prev_fd = -1;
// 	t_node **groups;
// 	int num_groups;
// 	char **cmd2;
// 	int i = 0;
// 	pid_t	id;
	
// 	groups = split_nodes_by_pipe(nodes, &num_groups);
// 	while (i < num_groups)
// 	{
// 		if (pipe(pip_fd) == -1)
// 			return (-1);
// 		id = fork();
// 		if (id == -1)
// 			return (-1);
// 		if (id == 0)
// 		{
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			if (i + 1 < num_groups)
// 				dup2(pip_fd[1], STDOUT_FILENO);
// 			close(pip_fd[1]);
// 			close(pip_fd[0]);
// 			cmd = loop_through_node(groups[i], NULL);
// 			cmd_path = is_accessable(fetch_path(my_env), cmd[0]);
// 			if (!cmd_path)
// 				exit(write(2, "mhd: command not found\n", 24));
// 			execve(cmd_path, cmd, load_env(my_env));
// 			perror("execeve (cmd2)");
// 			exit(1);
// 		}
// 		else
// 		{
// 			if (prev_fd != -1)
// 				close(prev_fd);
// 			close(pip_fd[1]);
// 			prev_fd = pip_fd[0];
// 			i++;
// 		}
// 	}
// 	while (wait(NULL) > 0);
// 	return (0);
// }

void exec_commands(t_node *nodes, t_env *my_env)
{
	char *cmd_path;
	char **cmd;
	char **group_cmd;

	if (!cmd)
	{
		perror("Minishell");
		exit(1);
	}	
	group_cmd = each_group_cmd(nodes);
	if (piping_forking(cmd_path, cmd, group_cmd, nodes, my_env) == -1)
	{
		perror("Minishell");
		exit(1);
	}	
	return ;	
}
void	claiming_env(char **env_p, t_env *my_env)
{
	char	*tmp_key;
	char	*tmp_value;
	int		in_equal;
	int		i;
	t_list *nodes;

	nodes = NULL;
	i = 0;
	while (env_p[i])
	{
		in_equal = ft_strlcpy(env_p[i], md_strlen(env_p[i]));
		tmp_key = malloc((in_equal * sizeof(char) + 1));
		filling_tmp(tmp_key,env_p[i], in_equal);
		tmp_value = malloc(((md_strlen(env_p[i]) - in_equal) * sizeof(char)) + 1);
		if (env_p[i][in_equal] == '=')
			tmp_value = env_p[i] + (in_equal + 1);
		ft_lstadd_back_m(&my_env, ft_lstnew_m(tmp_key, tmp_value));
		i++;
	}
	exec_commands(nodes, my_env);
	return ;
}



int main(int argc, char **argv, char **envp)
{
	int i = 0;
	t_node *nodes;
	t_env *my_envp;
	char *input;

	nodes = NULL;
	my_envp = NULL;
	claiming_env(envp, my_envp);
	
	// signal(SIGINT, sigint_handler);
	// while (1)
	// {
	// 	input = readline("Moha_youss$ ");
	// 	if (!input)
	// 	{
	// 		printf("\nget out M.Y ...(Cntl + D)\n");
	// 		break ;
	// 	}

	// 	if (*input)
	// 		add_history(input);
	// 	printf("The Out out I entered is : %s\n", input);
	// 	free(input);
	// }
	// clear_history(); // Clean up history before exiting
	return (0);
}
