/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:21:56 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/15 18:02:40 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

// int is_directory(const char *path)
// {
//    int fd;

// 	fd = open(path, __O_DIRECTORY);
// 	if (fd)
// 		return (0);
// 	return (1);
// }

void filling_tmp(char *key,char *env, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
}
char **fetch_path(t_env *my_env)
{
	char *path_value;
	char **paths;
	while (my_env)
	{
		if (ft_strncmp(my_env->key, "PATH", 4) == 0)
		{
			path_value = my_env->value;
			paths = md_split(path_value, ':');
			return (paths);
		}
		my_env = my_env->next;
	}
	return (NULL);
}

// void print_node(t_env *my_env)
// {
// 	while (my_env)
// 	{
// 		printf("%s = %s\n", my_env->key, my_env->value);
// 		my_env = my_env->next;
// 	}
// }
// void print_node2(t_list *my_env)
// {
	// 	while (my_env)
	// 	{
		// 		printf("%s -> [%d]\n", my_env->data, my_env->type);
		// 		my_env = my_env->next;
		// 	}
		// }
char *is_accessable(char **path, char *cmd)
{
	int i;
	char *full_path;
	char *temp;

	i = 0;
	while (path[i])
	{
		temp = md_strjoin(path[i], "/");
		full_path = md_strjoin(temp, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	**create_full_cmd(t_list *nodes)
{
	char *tmp;
	char **full_cmd;

	full_cmd = NULL;
	tmp = NULL;
	while (nodes)
	{
		if (nodes->type == 5)
			break ;
		if (nodes->type == 1 || nodes->type == 2 || nodes->type == 3 || nodes->type == 4)
			break ;
		tmp = md_strjoin(tmp, nodes->data);
		tmp = md_strjoin(tmp, " ");
		nodes = nodes->next;
	}
	full_cmd = md_split(tmp, ' ');
	int i = 0;
	while (full_cmd[i])
	{
		printf("{%s},", full_cmd[i++]);
	}
	free(tmp);
	return (full_cmd);
}

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

char	**helper_loop(char **cmd, t_list *nodes)
{
	int i;
	int num_cmd;
	t_list *head;

	i = 0;
	head = nodes;
	num_cmd = 0;
	while (head)
	{
		if (nodes->type == 0)
			num_cmd++;
		head = head->next;
	}
	cmd = malloc(((num_cmd + 1) * sizeof(char *)));
	if (!cmd)
		return (NULL);
	while (nodes)
	{
		if (nodes->type == 0)
			cmd[i++] = nodes->data;
		nodes = nodes->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	redirection(t_list *nodes);

char	**loop_through_node(t_list *nodes, char **cmd)
{
	int fd;
	t_list *head;

	head = nodes;
	cmd = NULL;
	while (head)
	{
		if (head->type == 1)
		{
			fd = open(head->data, O_RDONLY);
			if (fd == -1)
	   			return (NULL);
		}
		else if (head->type == 2)
		{
			fd = open(head->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
	   			return (NULL);
			dup2(fd, STDOUT_FILENO);
		}
		head = head->next;
	}
	// redirection(nodes);
	cmd = helper_loop(cmd, nodes);
	return (cmd);
}

int	count_pipes(t_list *nodes)
{
	int num_pipes;

	num_pipes = 0;
	while (nodes)
	{
		if (nodes->type == 5)
			num_pipes++;
		nodes = nodes->next;
	}
	return (num_pipes);
}

void exec_commands(t_list *nodes, t_env *my_env)
{
	char **path;
	char *cmd_path;
	char **cmd;
	char **envirment;
	char **full_cmd;
	int id;
	int num_pipes;

	ft_lstadd_backk(&nodes, ft_lstneww("marn", 1));
	// ft_lstadd_backk(&nodes, ft_lstneww("lst_functions.c", 0));
	// ft_lstadd_backk(&nodes, ft_lstneww("mari", 2));
	// ft_lstadd_backk(&nodes, ft_lstneww("maro", 2));
	ft_lstadd_backk(&nodes, ft_lstneww("cat", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("|", 5));
	ft_lstadd_backk(&nodes, ft_lstneww("moha", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("uy", 0));
	cmd = loop_through_node(nodes, cmd);
	if (!cmd)
	{
		perror("Minishell");
		exit(1);
	}
	num_pipes = count_pipes(nodes);
	path = fetch_path(my_env);
	cmd_path = is_accessable(path, cmd[0]);
	if (!cmd_path)
	{
		write(2, "mhd: command not found\n", 24);
		exit(1);
	}
	full_cmd = create_full_cmd(nodes);
	envirment = load_env(my_env);
	execve(cmd_path, full_cmd, envirment);
	perror("execeve (cmd2)");
	exit(1);
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
		ft_lstadd_back(&my_env, ft_lstnew(tmp_key, tmp_value));
		i++;
	}
	exec_commands(nodes, my_env);
	// print_node(my_env);
	return ;
}



int main(int argc, char **argv, char **envp)
{
	int i = 0;
	t_list *nodes;
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
