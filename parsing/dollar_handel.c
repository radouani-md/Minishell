/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:23:38 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/22 19:54:09 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_dollar_quote_case_you(t_node *lst, t_ha *ha)
{
	ha->quote_count = 0;
	if (lst->data[ha->read_index + 1] == '\'' && ha->dbl_qte % 2 == 0)
		ha->quote_count = ha->snl_qte + 1;
	else if (lst->data[ha->read_index + 1] == '\"' && ha->snl_qte % 2 == 0)
		ha->quote_count = ha->dbl_qte + 1;
	if (ha->quote_count % 2 == 1)
		ha->read_index++;
	else
	{
		ha->dest_index++;
		ha->read_index++;
	}
}

void	copy_to_dap_you(char *str, t_ha *ha)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		(ha->dest_index)++;
		i++;
	}
}

void	ft_functin_env_you(t_ha *ha, t_ha *err)
{
	char	*str;
	int		i;

	i = 0;
	str = md_itoa(err->err_status);
	while (str[i])
	{
		ha->dest_index++;
		i++;
	}
}

void	copy_env_value_you(t_node *lst, t_env *my_env, t_ha *ha, t_ha *err)
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
			copy_to_dap_you(my_env->value, ha);
			break ;
		}
	}
	if (!ft_strncmp(src, "?", 1))
		ft_functin_env_you(ha, err);
}

int	count_cmd1(t_node *lst, t_env *my_env, t_ha *err)
{
	t_ha	*ha;

	ha = helper_varia(err->err_status);
	while (lst->data[ha->read_index])
	{
		conut_dabel_singel_qoutition(lst->data[ha->read_index], ha);
		if (check_dollar(lst, ha))
			copy_env_value_you(lst, my_env, ha, err);
		else
		{
			if (lst->data[ha->read_index] == '$'
				&& lst->data[ha->read_index + 1] == '$')
				count_dollare(ha, lst->data);
			else if (lst->data[ha->read_index] == '$'
				&& (lst->data[ha->read_index + 1] == '\"'
					|| lst->data[ha->read_index + 1] == '\''))
				handle_dollar_quote_case_you(lst, ha);
			else
			{
				ha->dest_index++;
				ha->read_index++;
			}
		}
	}
	return (ha->dest_index);
}
