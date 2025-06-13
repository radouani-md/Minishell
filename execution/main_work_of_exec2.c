/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_work_of_exec2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:27:42 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/13 12:29:51 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_md(t_md **md, t_node *nodes, t_env *my_env, t_ha *err)
{
	*md = gc_malloc(sizeof(t_md), 1);
	(*md)->prev_fd = -1;
	(*md)->is_entred = 0;
	(*md)->i = 0;
	(*md)->is_twice = 0;
	(*md)->pid = 0;
	if (spliting_nodes_hd(*md, nodes, my_env, err) == -333)
		return (-333);
	return (0);
}

void	helper_built(t_md *md, t_ha *err)
{
	md->cmd2 = loop_through_node_cmd(md->groups[md->i]);
	if (!md->cmd2)
	{
		gc_malloc(0, 0);
		exit(127);
	}
	err->err_status = 0;
}
