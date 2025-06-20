/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_types_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:40:09 by rd_md_haker       #+#    #+#             */
/*   Updated: 2025/06/16 17:57:40 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	implement_outfile(t_node *nodes, t_ha *err)
{
	int	fd;

	if (nodes->type == 1337)
		return (write(2, "minishell: ambiguous redirect\n", 30),
			err->err_status = 1, 3);
	fd = open(nodes->data, O_RDONLY);
	if (fd == -1)
		return (perror("mhd: "), err->err_status = 1, close(err->saved_fd), 3);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	implement_appending(t_node *nodes, t_ha *err)
{
	int	fd;

	if (nodes->type == 1337)
		return (write(2, "minishell: ambiguous redirect\n", 30),
			err->err_status = 1, 3);
	fd = open(nodes->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (perror("mhd: "), err->err_status = 1, close(err->saved_fd), 3);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	implement_infile(t_node *nodes, t_ha *err)
{
	int	fd;

	if (nodes->type == 1337)
		return (write(2, "minishell: ambiguous redirect\n", 30),
			err->err_status = 1, 3);
	fd = open(nodes->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("mhd: "), err->err_status = 1, close(err->saved_fd), 3);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	is_builtin(char *cmd)
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
		if (ft_strcmp(cmd, "unset") == 0)
			return (1);
	}
	return (0);
}
