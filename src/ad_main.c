/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:05:13 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:34:11 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

__attribute__((constructor)) void	check_for_interractive_mode(void)
{
	if (!isatty(STDIN_FILENO)
		|| !isatty(STDOUT_FILENO)
		|| !isatty(STDERR_FILENO))
		exit(EXIT_FAILURE);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	init_ms(t_ms *ms, char *av[], int ac, char *envp[])
{
	int	i;

	i = 1;
	ge_bzero(ms, sizeof(*ms));
	ms->errors |= init_env(&ms->env, envp);
	if (!av[0])
		av[0] = "minishell";
	ms->pname = _basename(av[0]);
	ms->msrc_fd = -1;
	ms->history_fd = -1;
	if (ac > 1)
	{
		while (i < ac)
		{
			parse_rc_file(ms, av[i]);
			++i;
		}
		ms_exit(ms->status, ms);
	}
	parse_rc_file(ms, MS_RC);
	ms->history_fd = ms_get_history_fd(&ms->prev_cmdline);
}

char	*get_cmd_line(t_ms *ms)
{
	char	*cmd_line;
	int		fd;
	int		ret_val;

	cmd_line = NULL;
	while (!cmd_line)
	{
		ms->status = update_sig(ms->status);
		make_prompt(ms->prompt, ms);
		set_sig(ROUTINE, ms);
		ret_val = get_cmd_line_fd(&fd, ms);
		if (ret_val == MS_RL_CTRLD)
			(close(fd), bi_exit(1, NULL, NULL, ms));
		else if (ret_val == MS_RL_RESTART_READ)
		{
			close(fd);
			continue ;
		}
		cmd_line = get_next_null_arco(fd);
		close(fd);
	}
	ms->status = update_sig(ms->status);
	return (cmd_line);
}

int	main(int ac, char **av, char **envp)
{
	char			*cmd_line;
	t_snippet		*lst;
	t_ms			ms;

	init_ms(&ms, av, ac, envp);
	while (1 && !ms.errors)
	{
		cmd_line = get_cmd_line(&ms);
		if (*cmd_line)
		{
			ms_add_history(cmd_line, ms.history_fd, &ms.prev_cmdline);
			lst = lexer(cmd_line);
			replace_aliases(&lst, &ms.table);
			cmd_line = (free(cmd_line), NULL);
			if (lst && check_syntaxe(lst, _basename(ms.pname)))
			{
				optimize_lst(&lst);
				exec_start(&ms, &lst);
			}
			else
				free_snip_lst(lst);
		}
		cmd_line = (free(cmd_line), NULL);
	}
	ms_exit(ms.errors, &ms);
}
