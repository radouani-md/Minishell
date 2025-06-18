/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yl_utils_func4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:24:41 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/18 11:24:42 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tchek_q(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

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

int	ft_strlen_num_err(t_ha *err)
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

int	check_after_dollar(char c)
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
