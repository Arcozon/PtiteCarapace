/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:08 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/09 17:05:34 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <readline/readline.h>
#include "libftprintf.h"
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "arcoms.h"

#define PROMPT_UNCLOSED "\1\033[1;90m\2> \1\033[0m\2"

void	ms_rdl(char *prompt, int fd)
{
	char	*ptr;
	char	*tmp;

	ft_putchar_fd('\n', fd);
	rl_on_new_line();
	ptr = readline(prompt);
	if (ptr && *ptr)
	{
		tmp = pass_whitespace(ptr);
		trim_trailling_ws(tmp);
		ft_putstr_fd(tmp, fd);
	}
	if (((ptr && !*ptr) || is_opened(ptr)))
	{
		free(ptr);
		return (ms_rdl(prompt, fd));
	}
	free(ptr);
}

// bool	is_opened(char *str)
// {
// 	static char	quote;
// 	static int	bracket;
// 	char		c;
// 	char		d;

// 	c = 0;
// 	d = 0;
// 	if (!str)
// 		return (quote || bracket > 0);
// 	while (*str)
// 	{
// 		if ((quote == '\'' && *str == '\'') || (quote == '\"' && *str == '\"'))
// 			quote = '\0';
// 		else if (!quote && (*str == '\'' || *str == '\"'))
// 			quote = *str;
// 		else if (!quote && (*str == '(' || *str == ')'))
// 			bracket += (int []){-1, 1}[*str == '('];
// 		d = c;
// 		c = *str;
// 		str++;
// 	}
// 	return (quote || bracket > 0 || c == '|' || (c == '&' && d == '&'));
// }

// int	wm_interpret(int missing)
// {
// 	return (!(missing == m_squote || missing == m_dquote));
// }

// void	wc_handle_quotes(int *missing, char quote)
// {
// 	if (*missing == m_dquote && quote == '"')
// 		*missing = -1;
// 	else if (*missing == m_squote && quote == '\'')
// 		*missing = -1;
// 	else if (!wm_interpret(*missing))
// 	{
// 		if (quote == '\'')
// 			*missing == m_squote;
// 		else
// 			*missing == m_dquote;
// 	}
// }	

// int	what_missing(char *str)
// {
// 	int	missing;
// 	int	i;

// 	missing = -1;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_strncmp(str[i], "&&", 2) && wm_interpret(missing))
// 			missing = (++i, m_and);
// 		else if (str[i] == '\'' || str[i] == '"')
// 			wc_handle_quotes(&missing, str[i]);		
// 		if (!ft_strncmp(str[i], "||", 2) && wm_interpret(missing))
// 			missing = (++i, m_or);
// 		else if (missing == m_or)
// 	}
// }

int	arco_ms_rdl(char *prompt, int fd, bool first)
{
	char	*ptr;
	char	*tmp;

	ft_putchar_fd('\n', fd);
	rl_on_new_line();
	ptr = readline(prompt);
	if (!ptr)
		return ((int []){MS_RL_RESTART_READ, MS_RL_CTRLD}[first]);
	if (ptr && *ptr)
	{
		tmp = pass_whitespace(ptr);
		trim_trailling_ws(tmp);
		ft_putstr_fd(tmp, fd);
	}
	if (((!first && ptr && !*ptr) || is_opened(ptr)))
	{
		free(ptr);
		return (arco_ms_rdl(PROMPT_UNCLOSED, fd, false));
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
	arl_status = arco_ms_rdl(ms->prompt, pipe_fds[1], true);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	if (g_sig == SIGINT)
		arl_status = MS_RL_RESTART_READ;
	free_ms(ms);
	exit(arl_status);
}

int	get_cmd_line_fd(int	*fd, t_ms *ms)
{
	int		pipe_fds[2];
	int		status;
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(pipe_fds[0]), close(pipe_fds[1]), -1);
	if (!pid)
		arco_rdl_child(pipe_fds, ms);
	close(pipe_fds[1]);
	status = 0;
	while (waitpid(pid, &status, 0) != pid)
	{
		g_sig = SIGINT; // ?
	}
	*fd = pipe_fds[0];
	return (get_exit_value(status));
}
