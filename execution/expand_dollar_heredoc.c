/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:55:54 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/18 18:34:29 by ylagzoul         ###   ########.fr       */
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

void	copy_env_value_heredoc(t_node *lst, t_env *my_env, char *dap, t_ha *err)
{
	int		b;
	char	*src;

	(err->read_index)++;
	src = env_key(err, lst->data);
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
			copy_to_dap_heredoc(dap, my_env->value, err);
			break ;
		}
	}
	if (!ft_strncmp(src, "?", 1))
		ft_functin_env(dap, err);
}

int	check_dollar_heredoc(t_node *lst, t_ha *ha)
{
	if (lst->data[ha->read_index] == '$')
	{
		if (lst->data[ha->read_index + 1] >= 97
			&& lst->data[ha->read_index + 1] <= 122)
			return (1);
		else if (lst->data[ha->read_index + 1] >= 65
			&& lst->data[ha->read_index + 1] <= 90)
			return (1);
		else if (lst->data[ha->read_index + 1] >= 48
			&& lst->data[ha->read_index + 1] <= 57)
			return (1);
		else if (lst->data[ha->read_index + 1] == 95
			|| lst->data[ha->read_index + 1] == '?')
			return (1);
	}
	return (0);
}

void	expanding_function_heredoc(t_node *lst, t_env *my_env, t_ha *err)
{
	char	*dap;

	err = helper_varia(err->err_status);
	dap = gc_malloc(sizeof(char) * (count_cmd(lst, my_env, err) + 1), 1);
	if (!dap)
		return ;
	while (lst->data[err->read_index])
	{
		if (check_dollar_heredoc(lst, err))
			copy_env_value_heredoc(lst, my_env, dap, err);
		else
		{
			if (lst->data[err->read_index] == '$'
				&& lst->data[err->read_index + 1] == '$')
				count_dollare(err, lst->data);
			else
				dap[err->dest_index++] = lst->data[err->read_index++];
		}
	}
	dap[err->dest_index] = '\0';
	lst->data = dap;
}
