/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:02 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/10 19:56:49 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	loop_through_node2(t_node **nodes, t_ha *err)
{
	if ((*nodes)->type == 2)
	{
		if (implement_infile((*nodes), err) == 1)
			return (1);
	}
	if ((*nodes)->type == 1)
	{
		if (implement_outfile((*nodes), err) == 1)
			return (1);
	}
	if ((*nodes)->type == 4)
	{
		if (implement_appending((*nodes), err))
			return (1);
	}
	return (0);
}

int	loop_through_node(t_node *nodes, char **cmd, t_env *env, t_ha *err)
{
	t_node	*head;
	int		is_entred;

	head = nodes;
	cmd = NULL;
	is_entred = 0;
	while (head)
	{
		if (head->type == 3 && is_entred != 1)
		{
			if (helper_her(head) == 1)
				return (1);
			is_entred = 1;
		}
		if (loop_through_node2(&nodes, err) == 1)
			return (1);
		head = head->next;
	}
	return (0);
}

int	loop_through_node_builtin2(t_node **nodes, t_ha *err, t_var *arm)
{
	if ((*nodes)->type == 2 || (*nodes)->type == 1337)
	{
		arm->in_var = implement_infile((*nodes), err);
		return (arm->in_var);
	}
	if ((*nodes)->type == 1 || (*nodes)->type == 1337)
	{
		arm->out_var = implement_outfile((*nodes), err);
		return (arm->out_var);
	}
	if ((*nodes)->type == 4 || (*nodes)->type == 1337)
	{
		arm->append_var = implement_appending((*nodes), err);
		return (arm->append_var);
	}
	return (0);
}

int	loop_through_node_builtin(t_node *nodes, t_env *env, t_ha *err)
{
	t_var	*arm;
	int		is_entred;
	int		returned_value;

	returned_value = 0;
	alloc_arm(&arm);
	is_entred = 0;
	while (nodes)
	{
		returned_value = loop_through_node_builtin2(&nodes, err, arm);
		if (returned_value)
			return (returned_value);
		if (nodes->type == 3 && is_entred != 1)
		{
			if (helper_her(nodes) == 1)
				return (1);
			is_entred = 1;
		}
		nodes = nodes->next;
	}
	return (0);
}

char	*is_accessable(char **path, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		if (access(cmd, X_OK) == 0)
			return (md_strdup(cmd));
		temp = md_strjoin(path[i], "/");
		full_path = md_strjoin(temp, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
