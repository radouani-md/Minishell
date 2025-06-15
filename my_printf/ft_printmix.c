/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 02:07:45 by ylagzoul          #+#    #+#             */
/*   Updated: 2025/06/15 02:07:57 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mix_printer(char caracter, va_list args)
{
	if (caracter == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (caracter == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (caracter == 'd' || caracter == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (caracter == 'u')
		return (ft_uns_putnbr(va_arg(args, unsigned int)));
	else if (caracter == 'x')
		return (ft_hexanbr(va_arg(args, unsigned int), 'x'));
	else if (caracter == 'X')
		return (ft_hexanbr(va_arg(args, unsigned int), 'X'));
	else if (caracter == 'p')
		return (ft_putpoint(va_arg(args, void *)));
	else
		return (ft_putchar(caracter));
}
