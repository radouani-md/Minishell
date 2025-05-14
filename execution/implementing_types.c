/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementing_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:07:48 by mradouan          #+#    #+#             */
/*   Updated: 2025/05/13 12:54:20 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper_her(char *tmp_name)
{
	int infile;
	
	infile = open(tmp_name, O_RDONLY);
	if (infile == -1)
		return (perror("files "), 1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	unlink(tmp_name);
	return (0);
}

char	*helper_her_doc2(char *line, t_env *env)
{
	char *dollar;
	char *trimmed;

	if (!line)
		return (perror("malloc "), NULL);
	dollar = md_strtrim(line, "$");
	trimmed = NULL;
	if (line[0] == '$')
	{
		while (env)
		{
			trimmed = md_strtrim(dollar, "\n");
			if (ft_strcmp(trimmed, env->key) == 0)
			{
				if (env->value)
				{
					dollar = md_strjoin(env->value, "\n");
					break ;
				}
			}
			env = env->next;
		}
	}
	if (trimmed)
		free(trimmed);
	return (dollar);
}

int helper_her_doc(char *del, int fd, t_env *env)
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
		if (!trimmed)
			return (perror("malloc "), 1);
		if (ft_strcmp(trimmed, del) == 0)
		{
			free(trimmed);
			free(line);
			break ;
		}
		line = helper_her_doc2(line, env);
		write(fd, line, md_strlen(line));
		free(trimmed);
        free(line);
	}
	close(fd);
	return (0);
}

int	count_heredoc(t_node *nodes)
{
	int num_heredocs;

	num_heredocs = 0;
	while (nodes)
	{
		if (nodes->type == 3)
			num_heredocs++;
		nodes = nodes->next;
	}
	return (num_heredocs);
}

int	implement_her_doc(t_node *nodes, t_env *env)
{
	int fd;
	char *tmp_name;
	int num_heredocs;

	num_heredocs = count_heredoc(nodes);
	while (nodes)
	{
		if (nodes->type == 3)
		{
			tmp_name = random_num();
			if (!tmp_name)
				return (1);
			fd = open(tmp_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1 || helper_her_doc(nodes->data, fd, env) == 1)
				return (1);
			num_heredocs--;
			if (num_heredocs)
				unlink(tmp_name);
		}
		nodes = nodes->next;
	}
	if (helper_her(tmp_name) == 1)
		return (1);
	free(tmp_name);
	return (0);
}

int	implement_appending(t_node *nodes)
{
	int	fd;

	fd = open(nodes->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (perror("fd "), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	implement_infile(t_node *nodes)
{
	int fd;

	fd = open(nodes->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		   return (perror("fd "), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

