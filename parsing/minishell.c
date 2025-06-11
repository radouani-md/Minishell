/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:01:57 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/11 23:22:21 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig_md ;

int	get_status(int status, int set_get)
{
	static int old_status = 0;
	
	if (set_get == 0)
	{
		old_status = status;
	}
	return (old_status);
}

int	exec_commands(t_node **nodes, t_env **my_env, t_ha *err)
{
	int returned_value;

	returned_value = piping_forking(nodes, my_env, err);
	if (returned_value == -333)
	{
		return (-333);
	}
	else if (returned_value == -1)
	{
		gc_malloc(0, 0);
		exit(1);
	}
	return (0);
}

void	sigint_handler(int sig)
{
	(void)sig;

	if (g_sig_md == 3)
	{
		close(0);
		write(1, "\n", 1);
		g_sig_md = 33;
	}
	if (g_sig_md == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_status(130, 0);
	}
	
}

void	setup_signals()
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
void ft_node(t_node **arg)
{
	t_node *tmp;
	t_node *tmp1;

	tmp = *arg;
	while(tmp)
	{
		if (tmp->data[0] == '\0')
		{
			if(!(*arg)->next)
			{
				*arg = NULL;
			}
			else
				tmp1->next = tmp->next;
		}
		tmp1 = tmp;
		tmp = tmp->next;
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	t_node	*arg;
	t_env	*my_envp;
	t_ha	*err;
	char	*input;

	err = gc_malloc(sizeof(t_ha), 1);
	err->err_status = 0;
	while (1)
	{
		err->saved_fd = dup(0);
		setup_signals();
		lst = NULL;
		g_sig_md = 0;
		err->err_status = get_status(err->err_status, 0);
		input = readline("minishell> ");
		err->err_status = get_status(0, 1);
		if (!input)
			return (printf("exit\n"), gc_malloc(0,0), close(err->saved_fd), 0);	
		if (input[0] == '\0')
		{
			close(err->saved_fd);
			continue ;
		}
		add_history(input);
		read_and_filling_node(input, &lst);
		if (lst == NULL)
		{
			close(err->saved_fd);
			continue ;
		}
		if(syntax_erorr(lst))
		{
			arg = typed_nodes(lst);
			if (!my_envp)
				claiming_env(envp, &my_envp);
			expand_variables(arg, my_envp, err);
			ft_node(&arg);
			delete_qoutation(arg);
			delete_sinqel_dabel_qoutishen(arg);
			if (exec_commands(&arg, &my_envp, err) == -333)
			{
				dup2(err->saved_fd, STDIN_FILENO);
				close(err->saved_fd);
				continue ;
			}
		}
		close(err->saved_fd);
	}
	return (gc_malloc(0, 0), 0);
}
