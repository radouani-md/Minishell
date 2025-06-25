/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:13:19 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/25 18:15:39 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	md_atoi_helper(char *str, long *exit_status, int sign, int *i)
{
	int				check;
	unsigned long	t;

	check = 0;
	t = 0;
	while (str[*i] && (str[*i] <= '9' && str[*i] >= '0'))
	{
		check = 1;
		if (t > (unsigned long)((9223372036854775807
				- (str[*i] - 48)) / 10))
			return (1);
		t = t * 10 + (str[*i] - 48);
		(*i)++;
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	if (str[*i] != '\0' || !check)
		return (1);
	*exit_status = t * sign;
	return (0);
}

long	md_atoi(char *str, long *exit_status)
{
	int				i;
	int				sign;

	i = -1;
	sign = 1;
	while (str[++i])
	{
		if ((str[i] > '9' || str[i] < '0')
			&& str[i] != '-' && str[i] != '+'
			&& str[i] != ' ' && str[i] != '\t')
			return (1);
	}
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (md_atoi_helper(str, exit_status, sign, &i) == 1)
		return (1);
	return (0);
}
