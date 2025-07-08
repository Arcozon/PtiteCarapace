/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:45:14 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/08 18:13:58 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int	g_sig = 0;

uint8_t	update_sig(uint8_t	status)
{
	if (g_sig)
		status = g_sig + STT_SIG_BASE;
	g_sig = 0;
	return (status); 
}

void	sig_routine(int sig)
{
	if (sig == SIGINT)
	{
		// write(STDOUT_FILENO, "\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		g_sig = sig;
	}
}

void	sig_exec(int sig)
{
	if (sig == SIGQUIT || sig == SIGINT)
		g_sig = sig;
}

void	set_sig(enum e_sig mode, t_ms *ms)
{
	struct sigaction	s_setsig;

	s_setsig.sa_flags = 0;
	sigemptyset(&s_setsig.sa_mask);
	s_setsig.sa_handler = sig_exec;
	if (mode == ROUTINE)
		s_setsig.sa_handler = sig_routine;
	else if (mode == DEFLT_SIG)
		s_setsig.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &s_setsig, 0))
		(ms_perror(ms->pname, "Signal setting SIGINT"),
			ms_exit(ms->status, ms));
	s_setsig.sa_handler = SIG_IGN;
	if (mode == EXEC)
		s_setsig.sa_handler = sig_exec;
	else if (mode == DEFLT_SIG)
		s_setsig.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &s_setsig, 0))
		(ms_perror(ms->pname, "Signal setting SIGQUIT"),
			ms_exit(ms->status, ms));
}

void	capture_signal_hdoc(int status, t_ms *ms)
{
	static struct termios	orig;
	struct termios			tmp;

	if (status == SIG_HDOC_SET)
	{
		tcgetattr(STDIN_FILENO, &tmp);
		orig = tmp;
		tmp.c_lflag |= ICANON | ECHO | ISIG;
		tcsetattr(STDIN_FILENO, TCSANOW, &tmp);
		set_sig(HEREDOC, ms);
	}
	else if (status == SIG_HDOC_RESET)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &orig);
		set_sig(EXEC, ms);
	}
}
