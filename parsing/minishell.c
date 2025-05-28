/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:01:57 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/27 16:10:01 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_commands(t_node **nodes, t_env **my_env)
{
	char	*cmd_path;
	char	**cmd;

	cmd_path = NULL;
	cmd = NULL;	
	if (piping_forking(cmd_path, cmd, nodes, my_env) == -1)
	{
		perror("Minishell");
		exit(1);
	}
	return ;	
}
void delete_sinqel_dabel_qoutishen(t_node *arg)
{
	int i;

	while(arg)
	{
		i = 0;
		while(arg->data[i])
		{
			if(arg->data[i] == 14)
			{
				arg->data[i] = '\"';
			}
			else if(arg->data[i] == 15)
			{
				arg->data[i] = '\'';
			}
			i++;
		}
		arg = arg->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	// static int num_err;
	t_list *lst;
	t_node *arg;
	t_env *my_envp;
	char *input;

	lst = NULL;
	arg = NULL;
	input = NULL;
	my_envp = NULL;
	while (1)
	{
		lst = NULL;
		input = readline("minishell> ");
		if (!input)
			exit(0);
		if (input[0] == '\0')
			continue;
		add_history(input);
		if (read_and_filling_node(input, &lst))
		{
			if (lst == NULL)
				continue;
			if (syntax_erorr(lst))
			{
				arg = typed_nodes(lst);
				if (!my_envp)
					claiming_env(envp, &my_envp);
				expand_variables(arg, my_envp);
				delete_qoutation(arg);
				delete_sinqel_dabel_qoutishen(arg);
				exec_commands(&arg, &my_envp);
				ft_free(&lst);
				ft_free1(&arg);
			}
			else
			    ft_free(&lst);
		}
		else
		    ft_free(&lst);
	}
	return (0);
}
