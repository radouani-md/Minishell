/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:30:26 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/04 16:31:48 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_puthex(unsigned long num, char *base)
{
	int		count;

	count = 0;
	if (num >= 16)
	{
		count += ft_puthex(num / 16, base);
		count += ft_puthex(num % 16, base);
	}
	else
		count += ft_putchar(base[num]);
	return (count);
}

int	ft_hexanbr(unsigned long ptr, char a)
{
	int	count;

	count = 0;
	if (a == 'x')
		return (count + ft_puthex(ptr, "0123456789abcdef"));
	else if (a == 'X')
		return (count + ft_puthex(ptr, "0123456789ABCDEF"));
	return (count);
}
