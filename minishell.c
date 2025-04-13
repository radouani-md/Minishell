/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:21:56 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/13 10:48:30 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

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
void	claiming_env(char **env_p, t_env *my_env)
{
	char	*tmp_key;
	char	*tmp_value;
	int		in_equal;
	int		i;

	// my_env = NULL;
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
	// print_node(my_env);
	return ;
}

void exec_commands(t_list *nodes)
{
	int i;

	i = 0;
	ft_lstadd_backk(&nodes, ft_lstneww("ls", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("-la", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("cat", 1));
	ft_lstadd_backk(&nodes, ft_lstneww("|", 5));
	ft_lstadd_backk(&nodes, ft_lstneww("yous", 0));
	ft_lstadd_backk(&nodes, ft_lstneww("uy", 0));
	
	// print_node2(nodes);
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
	
	exec_commands(nodes);
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
