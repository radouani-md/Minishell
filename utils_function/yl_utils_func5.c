/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 02:45:52 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/12 15:23:28 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar(t_node *lst, t_ha *ha)
{
	if (lst->data[ha->read_index] == '$' && ha->snl_qte % 2 == 0)
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

void	num_expd_out_qte(t_node *lst, t_env *my_env, t_ha *halel, t_ha *err)
{
	int		b;
	char	*src;

	(halel->read_index)++;
	if (check_after_dollar(lst->data[halel->read_index]))
		src = env_key(halel, lst->data);
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
			len_env_value_without_space(my_env->value, halel);
			break ;
		}
	}
	if (src[0] == '?')
		halel->dest_index += ft_strlen_num_err(err);
}

void	num_expd_qte(t_node *lst, t_env *my_env, t_ha *halel, t_ha *err)
{
	int		b;
	char	*src;

	halel->read_index++;
	if (check_after_dollar(lst->data[halel->read_index]))
		src = env_key(halel, lst->data);
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
			len_env_value(my_env->value, halel);
			break ;
		}
	}
	if (src[0] == '?')
		halel->dest_index += ft_strlen_num_err(err);
}

t_ha	*helper_varia(int err)
{
	t_ha	*new_node;

	new_node = gc_malloc(sizeof(t_ha), 1);
	new_node->dest_index = 0;
	new_node->err_status = err;
	new_node->read_index = 0;
	new_node->quote_count = 0;
	new_node->snl_qte = 0;
	new_node->dbl_qte = 0;
	new_node->next = NULL;
	return (new_node);
}

t_handel	*helper_variables(void)
{
	t_handel	*new_node;

	new_node = gc_malloc(sizeof(t_handel), 1);
	new_node->t = 0;
	new_node->a = 0;
	new_node->q = 1;
	new_node->quote_count = 1;
	new_node->next = NULL;
	return (new_node);
}
