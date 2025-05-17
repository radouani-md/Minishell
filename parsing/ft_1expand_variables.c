/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1expand_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:51:43 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/17 16:39:17 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_functin_env(char *dap, t_ha *ha)
{
	char	*str;
	int		i;

	i = 0;
	// int num_err = 0;
	str = "0"; // ft_itoa(num_err);
	while(str[i])
	{
		dap[(ha->dest_index)++] = str[i++];
	}
}

void	copy_to_dap(char *dap, char *str, t_ha *ha)
{
	int	i;
	int	m;

	i = 0;
	m = ft_strlen(ha->dest_index, dap);
	while (str[i])
	{
		if (m % 2 == 0)
		{
			while (str[i] == ' ')
				i++;
			if (str[i] != ' ')
			{
				if (str[i - 1] == ' ' && dap[0] != '\0')
					dap[(ha->dest_index)++] = str[i - 1];
				dap[(ha->dest_index)++] = str[i++];
			}
			if (str[i] == '\"')
				m++;
		}
		else
			dap[(ha->dest_index)++] = str[i++];
	}
}

char	*env_key(t_ha *ha, char *str)
{
	int		cpy_index;
	int		dest_index;
	int		len_key;
	char	*src;

	len_key = 0;
	cpy_index = ha->read_index;
	dest_index = 0;
	while (ft_Check_after_dollar(str[cpy_index]))
	{
		len_key++;
		if (str[cpy_index - 1] == '$' && ((str[cpy_index] >= 48 && str[cpy_index] <= 57)
				|| str[cpy_index] == '?'))
			break ;
		cpy_index++;
	}
	src = malloc(sizeof(char) * (len_key + 1));
	if (!src)
		return (NULL);
	while (ft_Check_after_dollar(str[ha->read_index]))
	{
		src[dest_index++] = str[(ha->read_index)++];
		if(((str[ha->read_index - 1] >= 48 && str[ha->read_index - 1] <= 57)
			|| str[ha->read_index - 1] == '?') && str[ha->read_index - 2] == '$')
			break ;
	}
	src[dest_index] = '\0';
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
	if (ft_strncmp1(src, "?", 1))
		ft_functin_env(dap, ha);
	// free(src);
}
