/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:31:16 by mradouan          #+#    #+#             */
/*   Updated: 2025/06/22 20:46:04 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_status(int status, int set_get)
{
	static int	old_status = 0;

	if (set_get == 0)
	{
		old_status = status;
	}
	return (old_status);
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_sig_md == 3)
	{
		close(0);
		write(1, "^C", 2);
		g_sig_md = 33;
	}
	if (g_sig_md == 0)
	{
		write(1, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_status(130, 0);
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction (SIGINT, &sa, NULL);
	signal (SIGQUIT, SIG_IGN);
}

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
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGQUIT)
					write(2, "Quit (core dumped)\n", 19);
				else if (sig == SIGINT)
					write(2, "\n", 1);
				err->err_status = 128 + sig;
			}
			else if (WIFEXITED(status))
				err->err_status = WEXITSTATUS(status);
		}
		wpid = wait(&status);
	}
}
