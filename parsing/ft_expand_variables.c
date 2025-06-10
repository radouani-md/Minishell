/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:13:58 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/10 20:44:03 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmd(t_node *lst, t_env *my_env, t_ha *err)
{
	t_ha	*halel;

	halel = helper_varia();
	while (lst->data[halel->read_index])
	{
		if (lst->data[halel->read_index] == '\''
			&& halel->dbl_qte % 2 == 0)
			halel->snl_qte++;
		else if (lst->data[halel->read_index] == '\"'
			&& halel->snl_qte % 2 == 0)
			halel->dbl_qte++;
		if (ft_Check_dollar(lst, halel))
		{
			if (halel->dbl_qte % 2 == 1)
				numstr_expand_with_quote(lst, my_env, halel, err);
			else
				numstr_expand_without_quote(lst, my_env, halel, err);
		}
		else
		{
			halel->read_index++;
			halel->dest_index++;
		}
	}
	return (halel->dest_index);
}

void	handle_dollar_quote_case(t_node *lst, t_ha *ha, char *dap)
{
	if (lst->data[ha->read_index + 1] == '\'' && ha->dbl_qte % 2 == 0)
		ha->quote_count = ha->snl_qte + 1;
	else if (lst->data[ha->read_index + 1] == '\"' && ha->snl_qte % 2 == 0)
		ha->quote_count = ha->dbl_qte + 1;
	if (ha->quote_count % 2 == 1)
		ha->read_index++;
	else
		dap[ha->dest_index++] = lst->data[ha->read_index++];
}

void	expanding_function(t_node *lst, t_env *my_env, t_ha *ha)
{
	char	*dap;
	// t_ha	*ha;

	ha = helper_varia(ha);
	dap = gc_malloc(count_cmd1(lst, my_env, ha) + 1, 1);
	while (lst->data[ha->read_index])
	{
		conut_dabel_singel_qoutition(lst->data[ha->read_index], ha);
		if (ft_Check_dollar(lst, ha))
			copy_env_value(lst, my_env, dap, ha);
		else
		{
			if (lst->data[ha->read_index] == '$'
				&& lst->data[ha->read_index + 1] == '$')
				count_dollare(ha, lst->data);
			else if (lst->data[ha->read_index] == '$'
				&& (lst->data[ha->read_index + 1] == '\"'
					|| lst->data[ha->read_index + 1] == '\''))
				handle_dollar_quote_case(lst, ha, dap);
			else
				dap[ha->dest_index++] = lst->data[ha->read_index++];
		}
	}
	dap[ha->dest_index] = '\0';
	fill_up_node(dap, lst);
}

void	is_quoted(t_node *lst)
{
	int	a;

	a = 0;
	while (lst->data[a])
	{
		if (lst->data[a] == '\"' || lst->data[a] == '\'')
		{
			lst->is_quoted = 1;
			break ;
		}
		else
			lst->is_quoted = 0;
		a++;
	}
}

void	expand_variables(t_node *lst, t_env *my_env, t_ha *err)
{
	t_ha	*ha;

	ha = helper_varia();
	while (lst)
	{
		ha->read_index = 0;
		while (lst->data[ha->read_index])
		{
			conut_dabel_singel_qoutition(lst->data[ha->read_index], ha);
			if (lst->data[ha->read_index] == '$'
				&& (ha->snl_qte % 2 == 0) && lst->type != 3)
			{
				expanding_function(lst, my_env, err);
				break ;
			}
			else if (lst->type == 3)
			{
				is_quoted(lst);
			}
			ha->read_index++;
		}
		lst = lst->next;
	}
}
