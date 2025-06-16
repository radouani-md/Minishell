/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:49:42 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/15 17:56:26 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exec_errors(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
	{
		ft_print_erorr("minishell: ", path,
			": No such file or directory\n", NULL);
		return (127);
	}
	if (S_ISDIR(buf.st_mode))
	{
		ft_print_erorr("minishell: ", path, ": Is a directory\n", NULL);
		return (126);
	}
	if (access(path, X_OK) == -1)
	{
		ft_print_erorr("minishell: ", path, ": Permission denied\n", NULL);
		return (126);
	}
	return (0);
}

int	md_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

void	md_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}
