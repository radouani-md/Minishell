/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:36:35 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/02 22:53:25 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	len_env_value(char *str, t_ha *halel)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		(halel->dest_index)++;
	}
}

int	ft_strlen_num_err(t_err *err)
{
	int		i;
	char	*str;

	i = 0;
	str = md_itoa(err->err_status);
	while (str[i])
		i++;
	return (i);
}

void	len_env_value_without_space(char *str, t_ha *halel)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ' && str[i])
	{
		i++;
		(halel->dest_index)++;
	}
}

int	ft_Check_after_dollar(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 48 && c <= 57)
		return (1);
	else if (c == 95 || c == '?')
		return (1);
	return (0);
}

int	ft_Check_dollar(t_node *lst, t_ha *ha)
{
	if (lst->data[ha->read_index] == '$' && ha->singl_qoute % 2 == 0)
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

void	numstr_expand_without_quote(t_node *lst, t_env *my_env, t_ha *halel, t_err *err)
{
	int		b;
	char	*src;

	(halel->read_index)++;
	if (ft_Check_after_dollar(lst->data[halel->read_index]))
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

void	numstr_expand_with_quote(t_node *lst, t_env *my_env, t_ha *halel, t_err *err)
{
	int		b;
	char	*src;

	halel->read_index++;
	if (ft_Check_after_dollar(lst->data[halel->read_index]))
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
