/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementing_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:07:48 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/16 20:49:45 by mradouan         ###   ########.fr       */
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

void	expand_hd(t_node **line_node, t_env *env, int is_quoted, t_ha *err)
{
	ft_lstadd_front(line_node, ft_lstnew1(err->line, 0));
	if (is_quoted == 0)
		expanding_function_heredoc(*line_node, env, err);
}

int	helper_her_doc(char *del, t_env *env, int is_quoted, t_ha *err)
{
	t_node	*line_node;

	line_node = NULL;
	g_sig_md = 3;
	while (1)
	{
		err->line = readline("heredoc> ");
		if (g_sig_md == 33)
			return (free(err->line), close(err->fd),
				err->err_status = 130, -333);
		if (!err->line)
		{
			ft_print_erorr("bash: warning: here-document delimited by",
				" end-of-file (wanted `", del, "')\n");
			break ;
		}
		if (ft_strcmp(err->line, del) == 0)
			break ;
		expand_hd(&line_node, env, is_quoted, err);
		write(err->fd, line_node->data, md_strlen(line_node->data));
		write(err->fd, "\n", 1);
		free(err->line);
	}
	return (free(err->line), close(err->fd), 0);
}

void	count_heredoc(t_node *nodes, t_ha *err)
{
	int	num_heredocs;

	num_heredocs = 0;
	while (nodes)
	{
		if (nodes->type == 3)
			num_heredocs++;
		if (num_heredocs > 16)
		{
			close(err->saved_fd);
			exit(2);
		}
		nodes = nodes->next;
	}
}

int	implement_her_doc(t_node *nodes, t_env *env, t_ha *err)
{
	char	*tmp_name;

	tmp_name = NULL;
	count_heredoc(nodes, err);
	while (nodes)
	{
		if (nodes->type == 3)
		{
			tmp_name = random_num();
			err->fd = open(tmp_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (err->fd == -1)
				return (perror("fd :"), 1);
			if (helper_her_doc(nodes->data, env, nodes->is_quoted, err) == -333)
				return (-333);
			nodes->tmp_file = md_strdup(tmp_name);
		}
		nodes = nodes->next;
	}
	return (0);
}
