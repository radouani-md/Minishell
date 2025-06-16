/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implementing_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:07:48 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/16 15:32:23 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	helper_her(t_node *nodes)
{
	while (nodes)
	{
		if (nodes->type == 3)
		{
			dup2(nodes->heredoc_fd, STDIN_FILENO);
			close(nodes->heredoc_fd);
		}
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

int	helper_her_doc(char *del, t_env *env, int is_quoted, t_ha *err, int pip_hd)
{
	t_node	*line_node;

	line_node = NULL;
	g_sig_md = 3;
	while (1)
	{
		err->line = readline("heredoc> ");
		if (g_sig_md == 33)
			return (free(err->line),
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
		write(pip_hd, line_node->data, md_strlen(line_node->data));
		write(pip_hd, "\n", 1);
		free(err->line);
	}
	return (free(err->line), 0);
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
			return (1);
		nodes = nodes->next;
	}
	return (0);
}

int create_heredoc(t_node **nodes, t_env *env, t_ha *err)
{
	int			pip_hd[2];
					
    if (pipe(pip_hd) == -1)
        return (perror("mhd"), 1);
    if (helper_her_doc((*nodes)->data, env, (*nodes)->is_quoted, err, pip_hd[1]) == -333)
    {
        close(pip_hd[0]);
        close(pip_hd[1]);
        return (-333);
    }

    close(pip_hd[1]);
    (*nodes)->heredoc_fd = pip_hd[0];
    return (0);
}

int	implement_her_doc(t_node *nodes, t_env *env, t_ha *err)
{
	if (count_heredoc(nodes))
	{
		close(err->saved_fd);
		exit(2);
	}
	while (nodes)
	{
		nodes->heredoc_fd =  -1;
		if (nodes->type == 3)
		{
			if (create_heredoc(&nodes, env, err) == -333)
				return (-333);
		}
		nodes = nodes->next;
	}
	return (0);
}
