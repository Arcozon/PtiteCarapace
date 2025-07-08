/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:05:13 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 14:47:45 by gaeudes          ###   ########.fr       */
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

char	*cpy_without_quote(char *str)
{
	int		len;
	char	*dup;
	int		i;
	char	*ptr;

	if (!str)
		return (0);
	len = ft_strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
			dup[i++] = *(str++);
		else
		{
			ptr = ft_strchr(str + 1, *str);
			while (++str != ptr)
				dup[i++] = *str;
			str++;
		}
	}
	dup[i] = 0;
	return (dup);
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
		{
			// if (ft_strchr(ptr->ptr, '\'') || ft_strchr(ptr->ptr, '"'))
			// {
			// 	tmp = cpy_without_quote(ptr->ptr);
			// 	free(ptr->ptr);
			// 	ptr->ptr = tmp;
			// }
			ptr = ptr->next;
		}
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

int	ft_strncmp_weq(char *name, char *env_var, size_t n)
{
	while (n && *name)
	{
		if (*name != *env_var)
			return (1);
		--n;
		++name;
		++env_var;
	}
	if (!n && *env_var == '=')
		return (0);
	return (1);
}

char	*expand(char **env, char *var_name, int len)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp_weq(var_name, env[i], len))
		i++;
	if (env[i])
		return (env[i] + len + 1);
	return (NULL);
}

size_t	write_snip(char *str, char *quote, int len)
{
	int	i;

	if (!str || !quote || !*str)
		return (0);
	i = 0;
	while (str[i] && i < len)
	{
		if (!*quote && (str[i] == '\'' || str[i] == '"'))
			*quote = str[i];
		else if (*quote == str[i])
			*quote = 0;
		if (str[i] == ' ' && !*quote)
		{
			return (write(STDOUT_FILENO, str, i));
			return (write(STDOUT_FILENO, str, i), write(2, str, i));
		}
		i++;
	}
	// return (write(STDOUT_FILENO, str, i), write(2, str, i));
	return (write(STDOUT_FILENO, str, i));
}

void	write_without_quote(char *str, int len)
{
	int		i;
	int		len_to_write;
	char	*ptr;

	if (!str)
		return ;
	i = 0;
	while (*str && i < len)
	{
		if (*str != '\'')
			ft_putchar_fd(*str, STDOUT_FILENO);
		else
		{
			str++;
			ptr = ft_strchr(str, '\'');
			len_to_write = ptr - str;
			i += len_to_write + 2;
			write(STDOUT_FILENO, str, len_to_write);
			str = ptr;
		}
		str++;
		i++;
	}
}

void	dollar_exp(char *ptr, char scope, char *quote)
{
	size_t	test;

	if (ptr && !scope)
	{
		while (*ptr)
		{
			test = write_snip(ptr, quote, ft_strlen(ptr));
			if (test != ft_strlen(ptr))
				write(1, "\0", 1);
			ptr += test;
			ptr = pass_whitespace(ptr);
		}
	}
	else if (ptr)
		write_without_quote(ptr, ft_strlen(ptr));
}

void	put_to_zero(int *i, char *quote)
{
	if (i)
		*i = 0;
	if (quote)
		*quote = 0;
}


void	expand_token(char *ptr, t_ms *ms, int len, char scope)
{
	int		wlen;
	int		i;
	char	quote;

	put_to_zero(&i, &quote);
	while (*ptr && i < len)
	{
		wlen = get_wlen(ptr, len);
		// arc_get_wlen(ptr, len, ms->env.tab);
		// fprintf(stderr, "[%d] %.*s\n", wlen, wlen, ptr);
		if (*ptr == '"')
			expand_token(ptr + 1, ms, wlen - 2, *ptr);
		else
		{
			if (*ptr == '$' && wlen != 1 && ft_strncmp("$$", ptr, 2))
			{
				if (wlen == 2 && !ft_strncmp("$?", ptr, wlen))
					ft_putnbr_fd(ms->status, STDOUT_FILENO);
				else
					dollar_exp(expand(ms->env.tab, ptr + 1, wlen - 1), scope, &quote);
			}
			else
				write_without_quote(ptr, wlen);
		}
		ptr += wlen;
		i += wlen;
	}
}

__attribute__((constructor)) void check_for_interractive_mode(void)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
		exit(EXIT_FAILURE);
}

const char *token_to_string(enum e_token token)
{
	switch (token)
	{
		case word: return ("word");
		case redir_in: return ("redir_in");
		case redir_out: return ("redir_out");
		case here_doc: return ("here_doc");
		case append: return ("append");
		case pipe_delim: return ("pipe_delim");
		case or: return ("or");
		case and: return ("and");
		case semicolon: return ("semicolon");
		case open_par: return ("open_par");
		case closing_par: return ("closing_par");
		case env_var: return ("env_var");
		default: return ("unknown");
	}
}

void print_snippet_list(t_snippet *head)
{
	while (head != NULL)
	{
		printf("Token: %-12s | Value: %s\n", token_to_string(head->token), head->ptr ? head->ptr : "(null)");
		head = head->next;
	}
}
int	main(int ac, char **av, char **envp)
{
	char			*str;
	int				fd;
	int				ret_val;
	t_snippet		*lst = NULL;
	t_ms			ms;

	ge_bzero(&ms, sizeof(ms));
	ms.errors |= init_env(&ms.env, envp);
	if (!av[0])
		av[0] = "minishell";
	ms.pname = _basename(av[0]);

	parse_rc_file(&ms, MS_RC);

	// Getting .ms_history fd
	ms.history_fd = ms_get_history_fd(&ms.prev_cmdline);
	// Main loop
	while (1)
	{
		ms.status = update_sig(ms.status);
		make_prompt(ms.prompt, &ms);
		set_sig(ROUTINE, &ms);
		ret_val = get_cmd_line_fd(&fd, &ms);
		if (ret_val == MS_RL_CTRLD)// || signal(SIGINT, SIG_IGN) == SIG_ERR)
			(close(fd), bi_exit(1, NULL, NULL, &ms));
		else if (ret_val == MS_RL_RESTART_READ)
		{
			close(fd);
			continue ;
		}
		str = get_next_null_arco(fd);
		close(fd);
		if (g_sig)
			ms.status = update_sig(ms.status);
		if (*str)
		{
			ms_add_history(str, ms.history_fd, &ms.prev_cmdline);
			lst = lexer(str);
			if (!lst)
			{
				free(str);
				continue ;
			}
			if (check_syntaxe(lst, _basename(av[0])))
			{
				// print_snippet_list(lst);
				replace_aliases(&lst, &ms.table);
				optimize_lst(&lst);// et celle ci seront a appeler dans l'exec
				replace_wildcards(&lst);// cette fonction 
				replace_tilde(lst, expand(ms.env.tab, "HOME", 4));
				exec_start(&ms, &lst);
			}
			else
				free_snip_lst(lst);
		}
		free(str);
		str = NULL;
	}
	(void)ac;(void)av;(void)envp;
	return (0);
}
