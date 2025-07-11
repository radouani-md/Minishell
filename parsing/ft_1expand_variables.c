/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1expand_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:23:28 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/21 17:57:11 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_dap(char *dap, char *str, t_ha *ha, int *i)
{
	if (str[*i] == '\"')
	{
		dap[(ha->dest_index)++] = 14;
		(*i)++;
	}
	else if (str[*i] == '\'')
	{
		dap[(ha->dest_index)++] = 15;
		(*i)++;
	}
	else
		dap[(ha->dest_index)++] = str[(*i)++];
}

void	copy_to_dap(char *dap, char *str, t_ha *ha)
{
	int	i;
	int	m;

	i = 0;
	m = ft_strlen(ha->dest_index, dap);
	if (str)
	{
		while (str[i])
		{
			if (m % 2 == 0)
			{
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				if ((str[i] != ' ' || str[i] != '\t') && str[i])
				{
					if (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t')
						&& dap[0] != '\0')
						dap[(ha->dest_index)++] = str[i - 1];
					store_dap(dap, str, ha, &i);
				}
			}
			else
				store_dap(dap, str, ha, &i);
		}
	}
}

void	store_str_src(t_ha *ha, char *str, char *src)
{
	int		dest_index;

	dest_index = 0;
	while (check_after_dollar(str[ha->read_index]))
	{
		src[dest_index++] = str[(ha->read_index)++];
		if (((str[ha->read_index - 1] >= 48 && str[ha->read_index - 1] <= 57)
				|| str[ha->read_index - 1] == '?')
			&& str[ha->read_index - 2] == '$')
			break ;
	}
	src[dest_index] = '\0';
}

char	*env_key(t_ha *ha, char *str)
{
	int		cpy_index;
	int		len_key;
	char	*src;

	len_key = 0;
	cpy_index = ha->read_index;
	while (check_after_dollar(str[cpy_index]))
	{
		len_key++;
		if (str[cpy_index - 1] == '$' && ((str[cpy_index] >= 48
					&& str[cpy_index] <= 57) || str[cpy_index] == '?'))
			break ;
		cpy_index++;
	}
	src = gc_malloc(len_key + 1, 1);
	store_str_src(ha, str, src);
	return (src);
}

void	copy_env_value(t_node *lst, t_env *my_env, char *dap, t_ha *ha)
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
			copy_to_dap(dap, my_env->value, ha);
			break ;
		}
	}
	check_ambegous(lst, my_env);
	if (!ft_strncmp(src, "?", 1))
		ft_functin_env(dap, ha);
}
