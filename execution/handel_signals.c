/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:31:16 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/13 12:32:06 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	catch_signals(t_ha *err, pid_t pid)
{
	pid_t	wpid;
	int		status;
	int		sig;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == pid)
		{
			if (WIFEXITED(status))
			{
				err->err_status = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
				else if (sig == SIGINT)
					write(1, "\n", 1);
				err->err_status = 128 + sig;
			}
		}
		wpid = wait(&status);
	}
}
