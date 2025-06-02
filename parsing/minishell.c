/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:01:57 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/02 11:14:56 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_commands(t_node **nodes, t_env **my_env, t_err *err)
{
	char	*cmd_path;
	char	**cmd;

	cmd_path = NULL;
	cmd = NULL;
	if (piping_forking(cmd_path, cmd, nodes, my_env, err) == -1)
	{
		perror("Minishell");
		exit(1);
	}
	return ;
}

void	sigint_handler(int sig)
{
	(void)sig;
	// t_err *err;

	// err->err_status = 130; //128 + SIGINT (2)
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction (SIGINT, &sa, NULL);
	signal (SIGQUIT, SIG_IGN);
}

void	delete_sinqel_dabel_qoutishen(t_node *arg)
{
	int	i;

	while (arg)
	{
		i = 0;
		while (arg->data[i])
		{
			if (arg->data[i] == 14)
			{
				arg->data[i] = '\"';
			}
			else if (arg->data[i] == 15)
			{
				arg->data[i] = '\'';
			}
			i++;
		}
		arg = arg->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	t_node	*arg;
	t_env	*my_envp;
	t_err	*err;
	char	*input;

	err = gc_malloc(sizeof(t_err), 1);
	err->err_status = 0;
	setup_signals();
	while (1)
	{
		lst = NULL;
		input = readline("minishell> ");
		if (!input)
			return (gc_malloc(0,0), printf("exit\n"), exit(0), 0);
		if (input[0] == '\0')
			continue ;
		add_history(input);
		read_and_filling_node(input, &lst);
		if (lst == NULL)
			continue ;
		syntax_erorr(lst);
		arg = typed_nodes(lst);
		if (!my_envp)
			claiming_env(envp, &my_envp);
		expand_variables(arg, my_envp, err);
		delete_qoutation(arg);
		delete_sinqel_dabel_qoutishen(arg);
		exec_commands(&arg, &my_envp, err);
	}
	return (gc_malloc(0, 0), 0);
}
