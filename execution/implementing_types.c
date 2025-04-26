/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementing_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:07:48 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/25 17:52:47 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper_her()
{
	int infile;
	
	infile = open(".tmp_file", O_RDONLY);
	if (infile == -1)
		return (-1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	unlink(".tmp_file");
	return (0);
}

int helper_her_doc(char *del, int fd)
{
	char	*line;
	char	*trimmed;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		trimmed = md_strtrim(line, "\n");
		if (ft_strcmp(trimmed, del) == 0)
		{
			free(trimmed);
			free(line);
			break ;
		}
		write(fd, line, md_strlen(line));
		free(trimmed);
        free(line);
	}
	close(fd);
	if (helper_her() == -1)
		return (-1);
	return (0);
}

int	implement_her_doc(t_node *nodes)
{
	int fd;

	fd = open(".tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (helper_her_doc(nodes->data, fd) == -1)
		return (-1);
	return (0);
}
int	implement_appending(t_node *nodes)
{
	int	fd;

	fd = open(nodes->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		   return (-1);
	dup2(fd, STDOUT_FILENO);
	return (0);
}

int	implement_infile(t_node *nodes)
{
	int	fd;

	fd = open(nodes->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		   return (-1);
	dup2(fd, STDOUT_FILENO);
	return (0);
}

