/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:45:14 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 18:05:39 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int g_sig = 0;

void	sig_exec(int sig)
{
	if (sig == SIGQUIT)
		fprintf(stderr, "SIGQUIT\n");
	if (sig == SIGINT)
		fprintf(stderr, "SIGINT\n");
	g_sig = sig;
}

void	set_sig_heredoc(void)
{
	struct sigaction	s_routine;

	s_routine.sa_flags = 0;
	s_routine.sa_handler = sig_exec;
	sigemptyset(&s_routine.sa_mask);
	if (sigaction(SIGINT, &s_routine, 0))
		exit(1);
	s_routine.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &s_routine, 0))
		exit(1);
}

void	set_sig_exec(void)
{
	struct sigaction	s_routine;

	s_routine.sa_flags = 0;
	s_routine.sa_handler = sig_exec;
	sigemptyset(&s_routine.sa_mask);
	if (sigaction(SIGINT, &s_routine, 0))
		exit(1);
	s_routine.sa_handler = sig_exec;
	if (sigaction(SIGQUIT, &s_routine, 0))
		exit(1);
}

void	capture_signal_hdoc(int status)
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
		set_sig_heredoc();
	}
	else if (status == SIG_HDOC_RESET)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &orig);
		set_sig_exec();
	}
}
