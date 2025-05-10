/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_sleep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:00:37 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/05/09 17:04:21 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_Check_dollar(t_node *lst, int i, int j)
{
	if (lst->data[i] == '$' && j % 2 == 0)
	{
		if (lst->data[i + 1] >= 97 && lst->data[i + 1] <= 122)
			return (1);
		else if (lst->data[i + 1] >= 65 && lst->data[i + 1] <= 90)
			return (1);
		else if (lst->data[i + 1] >= 48 && lst->data[i + 1] <= 57)
			return (1);
		else if (lst->data[i + 1] == 95 || lst->data[i + 1] == '?')
			return (1);
	}
	return (0);
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
