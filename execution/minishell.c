/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:21:56 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/17 23:51:23 by mradouan         ###   ########.fr       */
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

void	md_free(int **num)
{
	int i;

	i = 0;
	while (num[i])
		free(num[i++]);
	free(num);
}

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

void print_node(t_env *my_env)
{
	while (my_env)
	{
		printf("%s = %s\n", my_env->key, my_env->value);
		my_env = my_env->next;
	}
}
void print_node2(t_list *my_env)
{
	while (my_env)
	{
		printf("%s -> [%d]\n", my_env->data, my_env->type);
		my_env = my_env->next;
	}
}
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
		{
            nodes = nodes->next;
            continue ; 
        }
		tmp = md_strjoin(tmp, nodes->data);
		tmp = md_strjoin(tmp, " ");
		nodes = nodes->next;
	}
	full_cmd = md_split(tmp, ' ');
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
		if (head->type == 0)
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

char **each_group_cmd(t_list *nodes)
{
	char *tmp;
	char **full_group_cmd;

	full_group_cmd = NULL;
	tmp = NULL;
	while (nodes)
	{
		if (nodes->type == 5)
		{
			tmp = md_strjoin(tmp, nodes->data);
			nodes = nodes->next;
			continue ;
		}
		
		tmp = md_strjoin(tmp, nodes->data);
		tmp = md_strjoin(tmp, " ");
		nodes = nodes->next;
	}
	full_group_cmd = md_split(tmp, '|');
	free(tmp);
	return (full_group_cmd);
}

int help_split_node(t_list *nodes)
{
	t_list	*head;
	int 	num_groups;

	num_groups = 1;
	head = nodes;
	while (head)
	{
		if (head->type == 5)
			num_groups++;
		head = head->next;	
	}
	head = nodes;
	return (num_groups);
}

t_list	**split_nodes_by_pipe(t_list *nodes, int *num_groups)
{
	t_list 	**groups;
	t_list	*group;
	int 	i;
	t_list	*head;

	i = 0;
	*num_groups = help_split_node(nodes);
	groups = malloc((*num_groups + 1) * sizeof(t_list *));
	group = NULL;
	head = nodes;
	if (!groups)
		return (NULL);
	while (head)
	{
		if (head->type == 5)
		{
			groups[i++] = group;
			group = NULL;
		}
		else
			ft_lstadd_backk(&group, ft_lstneww(head->data, head->type));
		head = head->next;
	}
	groups[i] = group;
	groups[i + 1] = NULL;
	return (groups);
}

int	piping_forking(char *cmd_path, char **cmd, char **group_cmd, t_list *nodes, t_env *my_env)
{
	int pip_fd[2];
	int prev_fd = -1;
	t_list **groups;
	int num_groups;
	char **cmd2;
	int i = 0;
	pid_t	id;
	
	groups = split_nodes_by_pipe(nodes, &num_groups);
	while (i < num_groups)
	{
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
			cmd_path = is_accessable(fetch_path(my_env), cmd[0]);
			if (!cmd_path)
				exit(write(2, "mhd: command not found\n", 24));
			execve(cmd_path, cmd, load_env(my_env));
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

void exec_commands(t_list *nodes, t_env *my_env)
{
	char *cmd_path;
	char **cmd;
	// char **full_cmd;
	char **group_cmd;

	ft_lstadd_backk(&nodes, ft_lstneww("cat", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("minishell.h", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("mini", 2));
	ft_lstadd_backk(&nodes, ft_lstneww("|", 5));
	ft_lstadd_backk(&nodes, ft_lstneww("grep", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("int", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("|", 5));
	ft_lstadd_backk(&nodes, ft_lstneww("wc", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("-w", 0));

	if (!cmd)
	{
		perror("Minishell");
		exit(1);
	}	
	// full_cmd = create_full_cmd(nodes);
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
