/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementing_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:07:48 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/10 10:51:30 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper_her(t_node *nodes)
{
	int	infile;

	while (nodes)
	{
		if (nodes->type == 3)
		{
			infile = open(nodes->tmp_file, O_RDONLY);
			if (infile == -1)
				return (perror("files "), 1);
		}
		dup2(infile, STDIN_FILENO);
		close(infile);
		unlink(nodes->tmp_file);
		nodes = nodes->next;
	}
	return (0);
}

void	expand_hd(char *line, t_node **line_node, t_env *env, int is_quoted, t_err *err)
{
	ft_lstadd_front(line_node, ft_lstnew1(line, 0));
	if (is_quoted == 0)
		expanding_function_heredoc(*line_node, env, err);
}

int helper_her_doc(char *del, int fd, t_env *env, int is_quoted, t_err *err)
{
	char	*line;
	t_node	*line_node;

	line_node = NULL;
	line = NULL;
	g_sig_md = 3;
	while (1)
	{
		line = readline("heredoc> ");
		if (g_sig_md == 33)
		{
			close(fd);
			return (-333);
		}
		if (!line)
		{
			printf("bash: warning: here-document delimited by");
			printf(" end-of-file (wanted `%s')\n", del);
			break ;
		}
		if (ft_strcmp(line, del) == 0)
			break ;
		expand_hd(line, &line_node, env, is_quoted, err);
		write(fd, line_node->data, md_strlen(line_node->data));
		write(fd, "\n", 1);
	}
	close(fd);
	return (0);
}

int	count_heredoc(t_node *nodes)
{
	int	num_heredocs;

	num_heredocs = 0;
	while (nodes)
	{
		if (nodes->type == 3)
			num_heredocs++;
		if (num_heredocs > 16)
			exit(2);
		nodes = nodes->next;
	}
	return (num_heredocs);
}

int	implement_her_doc(t_node *nodes, t_env *env, t_err *err)
{
	char	*tmp_name;
	int		fd;
	int		num_heredocs;

	tmp_name = NULL;
	num_heredocs = count_heredoc(nodes);
	while (nodes)
	{
		if (nodes->type == 3)
		{
			tmp_name = random_num();
			fd = open(tmp_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
				return (perror("fd :"), 1);
			if (helper_her_doc(nodes->data, fd, env, nodes->is_quoted, err) == -333)
				return (-333);
			nodes->tmp_file = md_strdup(tmp_name);
			if (!nodes->tmp_file)
				return (perror("malloc "), 1);
		}
		nodes = nodes->next;
	}
	return (0);
}
