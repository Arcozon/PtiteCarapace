/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:08 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/04 18:49:21 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <readline/readline.h>
#include "libftprintf.h"
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "arcoms.h"

# define PROMPT_UNCLOSED "\1\033[1;90m\2> \1\033[0m\2"

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

void	rdl_child(int pipe_fds[2], pid_t pid, char *prompt, int history_fd)
{
	char	*ptr;
	void	*tmp;

	if (is_child(pid))
	{
		set_sigchild_handler(pipe_fds);
		ptr = readline(prompt);
		if (ptr && *ptr)
		{
			tmp = pass_whitespace(ptr);
			trim_trailling_ws(tmp);
			ft_putstr_fd(tmp, pipe_fds[1]);
			if (!*(char *)tmp)
				ft_putchar_fd(' ', pipe_fds[1]);
		}
		else if (ptr)
			ft_putchar_fd(' ', pipe_fds[1]);
		if (is_opened(ptr))
			ms_rdl("> ", pipe_fds[1]);
		(close(pipe_fds[0]), close(pipe_fds[1]), close(history_fd));
		return (free(ptr), exit(0));
		// return (free(ptr), exit((int []){0, 1}[g_sig == SIGINT])); //, free(prompt.prompt)
	}
}

int	arco_ms_rdl(char *prompt, int fd, bool first)
{
	char	*ptr;
	char	*tmp;

	ft_putchar_fd('\n', fd);
	rl_on_new_line();
	ptr = readline(prompt);
	if (!ptr)
		return (1);
	if (ptr && *ptr)
	{
		tmp = pass_whitespace(ptr);
		trim_trailling_ws(tmp);
		ft_putstr_fd(tmp, fd);
	}
	if (((!first && ptr && !*ptr) || is_opened(ptr)))
	{
		free(ptr);
		return (arco_ms_rdl(PROMPT_UNCLOSED, fd, 0));
	}
	free(ptr);
	return (0);
}

void	arco_rdl_child(int pipe_fds[2], char *prompt)
{
	int	arl_status;

	set_sigchild_handler(pipe_fds);
	rl_getc_function = getc;
	arl_status = arco_ms_rdl(prompt, pipe_fds[1], 1);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	// fprintf(stderr, "-[%d]-", arl_status);
	exit(arl_status);
}

int	get_cmd_line_fd(int	*fd, char *prompt, int history_fd)
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
		arco_rdl_child(pipe_fds, prompt);
	// rdl_child(pipe_fds, pid, prompt, history_fd);
	close(pipe_fds[1]);
	status = 0;
	if (waitpid(pid, &status, 0) != pid)
	{
		g_sig = SIGINT;
	}
	*fd = pipe_fds[0];
	// fprintf(stderr, "-{%d}-", get_exit_value(status));
	return (get_exit_value(status));
	(void)history_fd;
}
