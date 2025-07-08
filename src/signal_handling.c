/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:45:14 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/08 16:40:30 by gaeudes          ###   ########.fr       */
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
	if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	else if (sig == SIGINT)
		write(2, "\n", 1);
	g_sig = sig;
}


void	set_sig(enum e_sig mode, t_ms *ms)
{
	const __sighandler_t	handle_sigint[] = {sig_routine, sig_exec, sig_exec, SIG_DFL};
	const __sighandler_t	handle_sigquit[] = {SIG_IGN, sig_exec, SIG_IGN, SIG_DFL};
	struct sigaction	s_setsig;

	if (mode < 0 || mode > DEFLT_SIG )
	{
		write(2, "Sig ?\n", 7);
		return ;
	}
	s_setsig.sa_flags = 0;
	sigemptyset(&s_setsig.sa_mask);
	s_setsig.sa_handler = handle_sigint[mode];
	if (sigaction(SIGINT, &s_setsig, 0))
	{
		ms_perror(ms->pname, "Signal setting SIGINT");
		ms_exit(ms->status, ms);
	}
	s_setsig.sa_handler = handle_sigquit[mode];
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
