/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:01:57 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/16 17:04:25 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_md ;

int	exec_commands(t_node **nodes, t_env **my_env, t_ha *err)
{
	int	returned_value;

	returned_value = piping_forking(nodes, my_env, err);
	if (returned_value == -333)
	{
		return (-333);
	}
	else if (returned_value == -1)
	{
		close(err->saved_fd);
		gc_malloc(0, 0);
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

char	*safe_readline(t_ha *err, t_list **lst)
{
	char	*line;
	char	*input;
	int		status;

	err->saved_fd = dup(0);
	setup_signals();
	*lst = NULL;
	g_sig_md = 0;
	err->err_status = get_status(err->err_status, 0);
	line = readline("minishell> ");
	err->err_status = get_status(0, 1);
	status = err->err_status;
	if (!line)
		return (printf("exit\n"), close(err->saved_fd),
			gc_malloc(0, 0), exit(status), NULL);
	input = md_strdup(line);
	free(line);
	if (input[0] == '\0')
	{
		close(err->saved_fd);
		return (NULL);
	}
	add_history(input);
	return (input);
}

int	helper_main(char **envp, t_all *node)
{
	static int	is_entred = 0;

	if (node->lst == NULL)
		return (close(node->err->saved_fd), 1);
	if (syntax_erorr(node->lst))
	{
		node->arg = typed_nodes(node->lst);
		if (!node->my_env)
			claiming_env(envp, &(node->my_env), is_entred);
		is_entred = 1;
		expand_variables(node->arg, node->my_env, node->err);
		ft_node(&node->arg);
		delete_qoutation(node->arg);
		delete_sinqel_dabel_qoutishen(node->arg);
		if (exec_commands(&node->arg, &node->my_env, node->err) == -333)
			return (dup2(node->err->saved_fd, STDIN_FILENO),
				close(node->err->saved_fd), 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_all	*node;
	char	*input;

	node = gc_malloc(sizeof(t_all), 1);
	(void)argv;
	(void)argc;
	node->arg = NULL;
	node->my_env = NULL;
	// if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	// 	return (1);
	node->err = gc_malloc(sizeof(t_ha), 1);
	node->err->err_status = 0;
	while (1)
	{
		input = safe_readline(node->err, &(node->lst));
		if (!input)
			continue ;
		if (read_and_filling_node(input, &(node->lst)))
		{
			if (helper_main(envp, node))
				continue ;
		}
		close(node->err->saved_fd);
	}
	return (0);
}
