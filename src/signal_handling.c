/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:45:14 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/23 16:07:08 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int g_sig = 0;

void	sig_routine(int sig)
{
	if (sig == SIGINT)
	{
		// reset buffer
		g_sig = sig;
	}
}

void	sig_exec(int sig)
{
	if (sig == SIGQUIT || sig == SIGINT)
		g_sig = sig;
}

void	set_sig(enum e_sig	mode, t_ms *ms)
{
	struct sigaction	s_setsig;

	s_setsig.sa_flags = 0;
	sigemptyset(&s_setsig.sa_mask);
	s_setsig.sa_handler = sig_exec;
	if (mode == ROUTINE)
		s_setsig.sa_handler = sig_routine;
	if (sigaction(SIGINT, &s_setsig, 0))
	{
		ms_perror(ms->pname, "Signal setting SIGINT");
		ms_exit(ms->status, ms);
	}
	s_setsig.sa_handler = SIG_IGN;
	if (mode == EXEC)
		s_setsig.sa_handler = sig_exec;
	if (sigaction(SIGQUIT, &s_setsig, 0))
	{
		ms_perror(ms->pname, "Signal setting SIGQUIT");
		ms_exit(ms->status, ms);
	}
}

void	capture_signal_hdoc(int status, t_ms *ms)
{
	static struct termios	orig;
	struct termios			tmp;

	if (status == SIG_HDOC_SET)
	{
		tcgetattr(STDIN_FILENO, &tmp);
		orig = tmp;
		tmp.c_cc[VQUIT] = _POSIX_VDISABLE;
		tmp.c_lflag |= ICANON | ECHO ;
		tcsetattr(STDIN_FILENO, TCSANOW, &tmp);
		set_sig(HEREDOC, ms);
	}
	else if (status == SIG_HDOC_RESET)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &orig);
		set_sig(EXEC, ms);
	}
}
