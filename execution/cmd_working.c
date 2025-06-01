/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:14:02 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/01 16:18:17 by ylagzoul         ###   ########.fr       */
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
	groups = gc_malloc((*num_groups + 1) * sizeof(t_node *), 1);
	if (!groups)
		return (perror("malloc "), NULL);
	group = NULL;
	head = nodes;
	while (head)
	{
		if (head->type == 5)
		{
			groups[i++] = group;
			group = NULL;
		}
		else
			ft_lstadd_back1(&group, ft_lstnew2(head->data, head->type, head->tmp_file));
		head = head->next;
	}
	groups[i] = group;
	return (groups[i + 1] = NULL, groups);
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
	cmd = gc_malloc(((num_cmd + 1) * sizeof(char *)), 1);
	if (!cmd)
		return (perror("malloc "), NULL);
	while (nodes)
	{
		if (nodes->type == 0)
			cmd[i++] = nodes->data;
		nodes = nodes->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**loop_through_node(t_node *nodes, char **cmd, t_env *env, t_err *err)
{
	t_node *head;
	int 	is_entred;

	head = nodes;
	cmd = NULL;
	is_entred = 0;
	while (head)
	{
		if (head->type == 2)
		{
			if (implement_infile(head, err) == 1)
				return (NULL);
		}
		if (head->type == 3 && is_entred != 1)
		{
			if (helper_her(head) == 1)
				return (NULL);
			// if (implement_her_doc(head, env) == 3)
			// 	exit(1); // exit_code = 2
			is_entred = 1;
		}
		if (head->type == 1)
		{
			if (implement_outfile(head, err) == 1)
				return (NULL);
		}
		if (head->type == 4)
		{
			if (implement_appending(head, err))
				return (NULL);
		}
		head = head->next;
	}
	cmd = helper_loop(cmd, nodes);
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	loop_through_node_builtin(t_node *nodes, t_env *env, t_err *err)
{
	t_node *head;
	int in_var;

	head = nodes;
	in_var = 0;
	while (head)
	{
		if (head->type == 2)
		{
			in_var = implement_infile(head, err);
			if (in_var == 1)
				return (1);
			else if (in_var == 3)
				return (3);
		}
		// if (head->type == 3 && is_entred != 1)
		// {
		// 	if (implement_her_doc(head, env, err) == 1)
		// 		return (1);
		// 	is_entred = 1;
		// }
		if (head->type == 1)
		{
			if (implement_outfile(head, err) == 1)
				return (1);
		}
		if (head->type == 4)
		{
			if (implement_appending(head, err))
				return (1);
		}
		head = head->next;
	}
	return (0);
}

char	**loop_through_node_cmd(t_node *nodes)
{
	char **cmd;

	cmd = NULL;
	cmd = helper_loop(cmd, nodes);
	return (cmd);
}

char *is_accessable(char **path, char *cmd)
{
	int i;
	char *full_path;
	char *temp;

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

