/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:02 by mradouan          #+#    #+#             */
/*   Updated: 2025/04/24 15:46:57 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **each_group_cmd(t_node *nodes)
{
	char *tmp;
	char **full_group_cmd;

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
	free(tmp);
	return (full_group_cmd);
}

int help_split_node(t_node *nodes)
{
	t_node	*head;
	int 	num_groups;

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
	t_node 	**groups;
	t_node	*group;
	int 	i;
	t_node	*head;

	i = 0;
	*num_groups = help_split_node(nodes);
	groups = malloc((*num_groups + 1) * sizeof(t_node *));
	group = NULL;
	head = nodes;
	if (!groups)
		return (NULL);
	while (head)
	{
		if (head->type == 5)
		{
			groups[i++] = group;
			group = NULL;
		}
		else
			ft_lstadd_back1(&group, ft_lstnew1(head->data, head->type));
		head = head->next;
	}
	groups[i] = group;
	groups[i + 1] = NULL;
	return (groups);
}

char	**helper_loop(char **cmd, t_node *nodes)
{
	int i;
	int num_cmd;
	t_node *head;

	i = 0;
	head = nodes;
	num_cmd = 0;
	while (head)
	{
		if (head->type == 0)
			num_cmd++;
		head = head->next;
	}
	cmd = malloc(((num_cmd + 1) * sizeof(char *)));
	if (!cmd)
		return (NULL);
	while (nodes)
	{
		if (nodes->type == 0)
			cmd[i++] = nodes->data;
		nodes = nodes->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**loop_through_node(t_node *nodes, char **cmd)
{
	t_node *head;

	head = nodes;
	cmd = NULL;
	while (head)
	{
		if (head->type == 4)
			implement_appending(head);
		else if (head->type == 3)
			implement_her_doc(nodes);
		else if (head->type == 1)
			implement_outfile(head);
		else if (head->type == 2)
			implement_infile(head);
		head = head->next;
	}
	cmd = helper_loop(cmd, nodes);
	return (cmd);
}

char *is_accessable(char **path, char *cmd)
{
	int i;
	char *full_path;
	char *temp;

	i = 0;
	while (path[i])
	{
		temp = md_strjoin(path[i], "/");
		full_path = md_strjoin(temp, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

