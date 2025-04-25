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

void	helper_her_doc(int *fd)
{
	int infile;
	
	close(*fd);
	infile = open(".tmp_file", O_RDONLY);
	if (infile == -1)
	{
		perror("open heredoc");
		exit(1);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	unlink(".tmp_file");
}

void    implement_her_doc(char *delimeter)
{
	char *line;
	char *trimmed;
	int fd;

	fd = open(".tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc : open failed"));
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		trimmed = md_strtrim(line, "\n");
		printf("%zu\n", md_strlen(trimmed));
		printf("%s\n", delimeter);
		if (ft_strcmp(trimmed, delimeter) == 0)
		{
			free(trimmed);
			free(line);
			break ;
		}
		write(fd, line, md_strlen(line));
		free(trimmed);
        free(line);
	}
	helper_her_doc(&fd);
}
