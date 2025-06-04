/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:33:19 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/04 16:31:50 by mradouan         ###   ########.fr       */
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
