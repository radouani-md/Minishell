/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_working2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:59:49 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/21 20:34:30 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**each_group_cmd(t_node *nodes)
{
	char	*tmp;
	char	**full_group_cmd;

	full_group_cmd = NULL;
	tmp = NULL;
	while (nodes)
	{
		if (nodes->type == 5)
		{
			tmp = md_strjoin(tmp, nodes->data);
			nodes = nodes->next;
			continue ;
		}
		tmp = md_strjoin(tmp, nodes->data);
		tmp = md_strjoin(tmp, " ");
		nodes = nodes->next;
	}
	full_group_cmd = md_split(tmp, '|');
	return (full_group_cmd);
}

int	help_split_node(t_node *nodes)
{
	t_node	*head;
	int		num_groups;

	num_groups = 1;
	head = nodes;
	while (head)
	{
		if (head->type == 5)
			num_groups++;
		head = head->next;
	}
	head = nodes;
	return (num_groups);
}

t_node	**split_nodes_by_pipe(t_node *nodes, int *num_groups)
{
	t_node	**groups;
	t_node	*group;
	int		i;

	i = 0;
	group = NULL;
	*num_groups = help_split_node(nodes);
	groups = gc_malloc((*num_groups + 1) * sizeof(t_node *), 1);
	while (nodes)
	{
		if (nodes->type == 5)
		{
			groups[i++] = group;
			group = NULL;
		}
		else
			ft_lstadd_back1(&group,
				ft_lstnew2(nodes->data, nodes->type,
					nodes->tmp_file, nodes->heredoc_fd));
		nodes = nodes->next;
	}
	groups[i] = group;
	return (groups[i + 1] = NULL, groups);
}

char	**helper_loop(char **cmd, t_node *nodes)
{
	int		i;
	int		num_cmd;
	t_node	*head;

	i = 0;
	head = nodes;
	num_cmd = 0;
	while (head)
	{
		if (head->type == 0)
			num_cmd++;
		head = head->next;
	}
	cmd = gc_malloc(((num_cmd + 1) * sizeof(char *)), 1);
	while (nodes)
	{
		if (nodes->type == 0)
			cmd[i++] = nodes->data;
		nodes = nodes->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**loop_through_node_cmd(t_node *nodes)
{
	char	**cmd;

	cmd = NULL;
	cmd = helper_loop(cmd, nodes);
	return (cmd);
}
