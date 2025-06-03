/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:55:54 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/03 11:18:15 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_to_dap_heredoc(char *dap, char *str, t_ha *ha)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		dap[(ha->dest_index)++] = str[i++];
	}
}

void	copy_env_value_heredoc(t_node *lst, t_env *my_env, char *dap, t_ha *ha, t_err *err)
{
	int		b;
	char	*src;

	(ha->read_index)++;
	src = env_key(ha, lst->data);
	while (my_env)
	{
		b = 0;
		while (my_env->key[b])
		{
			if (my_env->key[b] != src[b])
				break ;
			b++;
		}
		if (my_env->key[b] || src[b])
			my_env = my_env->next;
		else
		{
			copy_to_dap_heredoc(dap, my_env->value, ha);
			break ;
		}
	}
	if (ft_strncmp1(src, "?", 1))
		ft_functin_env(dap, ha, err);
}

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

void	expanding_function_heredoc(t_node *lst, t_env *my_env, t_err *err)
{
	char	*dap;
	t_ha	*ha;
	
	ha = helper_varia();
	dap = gc_malloc(sizeof(char) * (count_cmd(lst, my_env, err) + 1), 1);//count_cmd(lst, my_env)
	if(!dap)
		return ;
	while (lst->data[ha->read_index])
	{
		if (check_dollar_heredoc(lst, ha))
			copy_env_value_heredoc(lst, my_env, dap, ha, err);
		else
		{
			if (lst->data[ha->read_index] == '$' && lst->data[ha->read_index + 1] == '$')
				count_dollare(ha, lst->data);
			else
				dap[ha->dest_index++] = lst->data[ha->read_index++];
		}
	}
	dap[ha->dest_index] = '\0';
	lst->data = dap;
}
