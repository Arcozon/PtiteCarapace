/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:08 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/10 17:38:31 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <sys/wait.h>
// #include <readline/readline.h>
// #include "libftprintf.h"
// #include <unistd.h>
// #include <stdlib.h>
#include "minishell.h"
#include "arcoms.h"

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

// int	arco_ms_rdl(char *prompt, int fd, bool first)
// {
// 	char	*ptr;
// 	char	*tmp;

// 	ft_putchar_fd('\n', fd);
// 	rl_on_new_line();
// 	ptr = readline(prompt);
// 	if (!ptr)
// 		return ((int []){MS_RL_RESTART_READ, MS_RL_CTRLD}[first]);
// 	if (ptr && *ptr)
// 	{
// 		tmp = pass_whitespace(ptr);
// 		trim_trailling_ws(tmp);
// 		ft_putstr_fd(tmp, fd);
// 	}
// 	if (((!first && ptr && !*ptr) || is_opened(ptr)))
// 	{
// 		free(ptr);
// 		return (arco_ms_rdl(PROMPT_UNCLOSED, fd, false));
// 	}
// 	return (free(ptr), 0);
// }

int	arco_ms_rdl_miss(char *prompt, int fd, t_ms *ms, uint32_t line)
{
	char	*ptr;
	char	*tmp;

	ft_putchar_fd('\n', fd);
	rl_on_new_line();
	ptr = readline(prompt);
	if (!ptr)
		return ((int []){MS_RL_RESTART_READ, MS_RL_CTRLD}[line == 0]);
	if (ptr && *ptr)
	{
		tmp = pass_whitespace(ptr);
		trim_trailling_ws(tmp);
		ft_putstr_fd(tmp, fd);
	}
	if (((!line && ptr && !*ptr) || is_opened(ptr)))
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
	// arl_status = arco_ms_rdl(ms->prompt, pipe_fds[1], true);
	arl_status = arco_ms_rdl_miss(ms->prompt, pipe_fds[1], ms, 0);
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
