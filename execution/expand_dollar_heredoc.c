/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:55:54 by mradouan          #+#    #+#             */
/*   Updated: 2025/05/28 16:00:37 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar_heredoc(t_node *lst, t_ha *ha)
{
	if (lst->data[ha->read_index] == '$')
	{
		if (lst->data[ha->read_index + 1] >= 97 && lst->data[ha->read_index + 1] <= 122)
			return (1);
		else if (lst->data[ha->read_index + 1] >= 65 && lst->data[ha->read_index + 1] <= 90)
			return (1);
		else if (lst->data[ha->read_index + 1] >= 48 && lst->data[ha->read_index + 1] <= 57)
			return (1);
		else if (lst->data[ha->read_index + 1] == 95 || lst->data[ha->read_index + 1] == '?')
			return (1);
	}
	return (0);
}

void	expanding_function_heredoc(t_node *lst, t_env *my_env)
{
	char	*dap;
	t_ha	*ha;
	
	ha = helper_varia();
	dap = malloc(sizeof(char) * (count_cmd(lst, my_env) + 1));
	if(!dap)
		return ;
	while (lst->data[ha->read_index])
	{
		conut_dabel_singel_qoutition(lst->data[ha->read_index], ha);
		if (check_dollar_heredoc(lst, ha))
			copy_env_value(lst, my_env, dap, ha);
		else
		{
			if (lst->data[ha->read_index] == '$' && lst->data[ha->read_index + 1] == '$')
				count_dollare(ha, lst->data);
			else if (lst->data[ha->read_index] == '$' && (lst->data[ha->read_index + 1] == '\"' || lst->data[ha->read_index + 1] == '\''))
			{
				if (lst->data[ha->read_index + 1] == '\'' && ha->dablla_qoute % 2 == 0)
					ha->quote_count = ha->singl_qoute + 1;
				else if (lst->data[ha->read_index + 1] == '\"' && ha->singl_qoute % 2 == 0)
					ha->quote_count = ha->dablla_qoute + 1;
				if (ha->quote_count % 2 == 1)
					ha->read_index++;
				else
					dap[ha->dest_index++] = lst->data[ha->read_index++];
			}
			else
				dap[ha->dest_index++] = lst->data[ha->read_index++];
		}
	}
	dap[ha->dest_index] = '\0';
	fill_up_node(dap, lst);
}
