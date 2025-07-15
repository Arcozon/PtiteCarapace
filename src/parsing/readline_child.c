/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:33:14 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	g_sig = sig;
}

void	set_sigchild_handler(int fds_to_close[2])
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		close(fds_to_close[0]);
		close(fds_to_close[1]);
		ft_putstr_fd("Error handling signal\n", 2);
		exit(1);
	}
}

bool	is_opened(char *str)
{
	static char	quote;
	static int	bracket;
	char		c;
	char		d;

	c = 0;
	d = 0;
	if (!str)
		return (quote || bracket > 0);
	while (*str)
	{
		if ((quote == '\'' && *str == '\'') || (quote == '\"' && *str == '\"'))
			quote = '\0';
		else if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (!quote && (*str == '(' || *str == ')'))
			bracket += (int []){-1, 1}[*str == '('];
		d = c;
		c = *str;
		str++;
	}
	return (quote || bracket > 0 || c == '|' || (c == '&' && d == '&'));
}

int	arco_ms_rdl_miss(char *prompt, int fd, t_ms *ms, uint32_t line)
{
	char	*ptr;

	ft_putchar_fd('\n', fd);
	rl_on_new_line();
	ptr = readline(prompt);
	if (!ptr)
		return ((int []){MS_RL_RESTART_READ, MS_RL_CTRLD}[line == 1]);
	if (ptr && *ptr)
		ft_putstr_fd(ptr, fd);
	if ((line > 1 && ptr && !*ptr) || is_opened(ptr))
	{
		make_prompt2(ms->prompt2, ms, what_missing(ptr), line);
		free(ptr);
		return (arco_ms_rdl_miss(ms->prompt2, fd, ms, line + 1));
	}
	free(ptr);
	return (0);
}

void	arco_rdl_child(int pipe_fds[2], t_ms *ms)
{
	int	arl_status;

	g_sig = 0;
	set_sigchild_handler(pipe_fds);
	rl_getc_function = getc;
	close(pipe_fds[0]);
	arl_status = arco_ms_rdl_miss(ms->prompt, pipe_fds[1], ms, 1);
	close(pipe_fds[1]);
	if (g_sig == SIGINT)
		arl_status = MS_RL_RESTART_READ;
	free_ms(ms);
	exit(arl_status);
}
