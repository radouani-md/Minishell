/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:01:57 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/14 16:21:23 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig_md ;

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
		close(err->saved_fd);
		exit(1);
	}
	return (0);
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
	tmp1 = NULL;
	while(tmp)
	{
		if (tmp->data[0] == '\0' && tmp->type != 2 && tmp->type != 4)
		{
			if(!(*arg)->next)
			{
				*arg = NULL;
			}
			else if (!tmp1)
			{
				*arg = tmp->next;
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

	(void)argv;
	(void)argc;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
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
			return (printf("exit\n"), close(err->saved_fd), gc_malloc(0, 0), 0);
		if (input[0] == '\0')
		{
			close(err->saved_fd);
			continue ;
		}
		add_history(input);
		if(read_and_filling_node(input, &lst))
		{
			if (lst == NULL)
			{
				close(err->saved_fd);
				continue ;
			}
			if (syntax_erorr(lst))
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
		}
		close(err->saved_fd);
	}
	return (gc_malloc(0, 0), free(input),0);
}
