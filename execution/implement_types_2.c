/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_types_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:40:09 by rd_md_haker       #+#    #+#             */
/*   Updated: 2025/05/10 10:00:28 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void safe_free(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

int implement_outfile(t_node *nodes)
{
	int fd;

	fd = open(nodes->data, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (0);
}

int is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "env") == 0)
			return (1);
		if (ft_strcmp(cmd, "cd") == 0)
			return (1);
		if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		if (ft_strcmp(cmd, "export") == 0)
			return (1);
		if (ft_strcmp(cmd, "echo") == 0)
			return (1);
		if (ft_strcmp(cmd, "exit") == 0)
			return (1);
	}
	return (0);
}

int exec_builtin(char **cmd, t_env **my_env, t_node **nodes)
{
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		implement_env(*my_env);
			return (1);
	}				
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (implement_cd(my_env, *nodes) == 1)
			return (1);
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		if (implement_pwd() == 0)
			return (1);
	}
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		if (implement_echo(*my_env, *nodes) == 0)
			return (1);
	}
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		if (implement_exit(my_env, nodes) == 0)
			return (1);
	}
	if (ft_strcmp(cmd[0], "export") == 0)
	{
	    if (implement_export(my_env, nodes) == 0)
	        return (1);
	}
	return (0);
}
