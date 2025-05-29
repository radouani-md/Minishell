/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:13:58 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/29 16:06:55 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmd(t_node *lst, t_env *my_env)
{
	t_ha	*halel;
	int		m;
	
	halel = helper_varia();
	while (lst->data[halel->read_index])
	{
		if (lst->data[halel->read_index] == '\'' && halel->dablla_qoute % 2 == 0)
			halel->singl_qoute++;
		else if (lst->data[halel->read_index] == '\"' && halel->singl_qoute % 2 == 0)
			halel->dablla_qoute++;
		if (ft_Check_dollar(lst, halel))
		{
			if (halel->dablla_qoute % 2 == 1)
				numstr_expand_with_quote(lst, my_env, halel);
			else
				numstr_expand_without_quote(lst, my_env, halel);
		}
		else
			halel->read_index = halel->read_index + halel->dest_index++;
	}
	m = halel->dest_index;
	return (m);
}

void	count_dollare(t_ha	*ha, char *lst)
{
	int	t;

	t = 0;
	while (lst[ha->read_index] == '$')
	{
		(ha->read_index)++;
		t++;
	}
	if (t % 2 == 1)
	{
		(ha->read_index)--;
	}
}

void	expanding_function(t_node *lst, t_env *my_env)
{
	char	*dap;
	t_ha	*ha;
	
	ha = helper_varia();
	dap = malloc(sizeof(char) * (200 + 1));//count_cmd(lst, my_env)
	if(!dap)
		return ;
	while (lst->data[ha->read_index])
	{
		conut_dabel_singel_qoutition(lst->data[ha->read_index], ha);
		if (ft_Check_dollar(lst, ha))
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

void expand_variables(t_node *lst, t_env *my_env)
{
	int	i;
	int	j;
	int	t;
	int a;

	j = 0;
	t = 0;
	while (lst)
	{
		i = 0;
		while (lst->data[i])
		{
			if (lst->data[i] == '\'' && t % 2 == 0)
				j++;
			else if (lst->data[i] == '\"' && j % 2 == 0)
				t++;
			if (lst->data[i] == '$' && (j % 2 == 0) && lst->type != 3)
			{
				expanding_function(lst, my_env);
				break ;
			}
			else if (lst->type == 3)
			{
				a = 0;
				while(lst->data[a])
				{
					if(lst->data[a] == '\"' || lst->data[a] == '\'')
					{
						lst->is_quoted = 1;
						break ;
					}
					else
						lst->is_quoted = 0;
					a++;
				}
			}
			i++;
		}
		lst = lst->next;
	}
}