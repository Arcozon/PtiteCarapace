/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:05:13 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 19:13:51 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "get_next_line.h"
#include "minishell.h"
#include "libftprintf.h"
#include "arcoms.h"

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

enum e_token	get_token(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (here_doc);
	if (*str == '<')
		return (redir_in);
	if (!ft_strncmp(str, ">>", 2))
		return (append);
	if (*str == '>')
		return (redir_out);
	if (!ft_strncmp(str, "||", 2))
		return (or);
	if (*str == '|')
		return (pipe_delim);
	if (!ft_strncmp(str, "&&", 2))
		return (and);
	if (*str == ';')
		return (semicolon);
	if (*str == '(')
		return (open_par);
	if (*str == ')')
		return (closing_par);
	return (word);
}

void	optimize_lst(t_snippet **head)
{
	t_snippet	*ptr;
	void		*tmp;

	ptr = *head;
	while (ptr)
	{
		if (is_redir(ptr->token) && ptr->next && ptr->next->token == word)
		{
			ptr->next->token = ptr->token;
			tmp = ptr->next->next;
			pop_snip(head, ptr);
			ptr = tmp;
		}
		else
			ptr = ptr->next;
	}
}

t_snippet	*lexer(char *str)
{
	int			len;
	t_snippet	*lst;
	char		*dup;

	if (!str)
		return (NULL);
	str = pass_whitespace(str);
	if (!*str)
		return (NULL);
	lst = NULL;
	while (*str)
	{
		len = word_len(str, simple_sep, ft_strlen(str));
		dup = ft_strndup(str, len);
		if (!dup || !add_to_snip_lst(&lst, get_token(dup), dup))
			return (free_snip_lst(lst), NULL);
		str += len;
		str = pass_whitespace(str);
	}
	return (lst);
}

__attribute__((constructor)) void	check_for_interractive_mode(void)
{
	if (!isatty(STDIN_FILENO)
		|| !isatty(STDOUT_FILENO)
		|| !isatty(STDERR_FILENO))
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

// int	main(int ac, char **av, char **envp)
// {
// 	char			*str;
// 	int				fd;
// 	int				ret_val;
// 	t_snippet		*lst;
// 	t_ms			ms;

// 	init_ms(&ms, av, ac, envp);
// 	while (1 && !ms.errors)
// 	{
// 		ms.status = update_sig(ms.status);
// 		make_prompt(ms.prompt, &ms);
// 		set_sig(ROUTINE, &ms);
// 		ret_val = get_cmd_line_fd(&fd, &ms);
// 		if (ret_val == MS_RL_CTRLD)
// 			(close(fd), bi_exit(1, NULL, NULL, &ms));
// 		else if (ret_val == MS_RL_RESTART_READ)
// 		{
// 			close(fd);
// 			continue ;
// 		}
// 		str = get_next_null_arco(fd);
// 		close(fd);
// 		ms.status = update_sig(ms.status);
// 		if (*str)
// 		{
// 			ms_add_history(str, ms.history_fd, &ms.prev_cmdline);
// 			lst = lexer(str);
// 			replace_aliases(&lst, &ms.table);
// 			str = (free(str), NULL);
// 			if (!lst)
// 				continue ;
// 			if (check_syntaxe(lst, _basename(ms.pname)))
// 			{
// 				optimize_lst(&lst);
// 				exec_start(&ms, &lst);
// 			}
// 			else
// 				free_snip_lst(lst);
// 		}
// 		str = (free(str), NULL);
// 	}
// 	ms_exit(ms.errors, &ms);
// }
