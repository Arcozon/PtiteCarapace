/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:03:17 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/10 17:41:26 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arcoms.h"

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

void	tilde_expansion(t_ms *ms, char c)
{
	char	*home;

	home = expand(ms->env.tab, HOME_VNAME, 4);
	if (!home)
		home = getenv(HOME_VNAME);
	ft_putstr_fd(home, STDOUT_FILENO);
	if (c == '/')
		write(STDOUT_FILENO, "/", 1);
}

void	write_token(t_ms *ms, char *ptr, int wlen, char scope)
{
	if (!scope && *ptr == '~'
		&& (is_white_space(ptr[1]) || ptr[1] == '/' || !ptr[1]))
		tilde_expansion(ms, ptr[1]);
	else if (!scope)
		write_without_quote(ptr, wlen);
	else
		write(STDOUT_FILENO, ptr, wlen);
}

void	expand_token(char *ptr, t_ms *ms, int len, char scp)
{
	int		wlen;
	int		i;
	char	q;

	put_to_zero(&i, &q);
	while (*ptr && i < len)
	{
		wlen = get_wlen(ptr, len);
		if (*ptr == '"')
			expand_token(ptr + 1, ms, wlen - 2, *ptr);
		else
		{
			if (*ptr == '$' && wlen != 1 && ft_strncmp("$$", ptr, 2))
			{
				if (wlen == 2 && !ft_strncmp("$?", ptr, wlen))
					ft_putnbr_fd(ms->status, STDOUT_FILENO);
				else
					dollar_exp(expand(ms->env.tab, ptr + 1, wlen - 1), scp, &q);
			}
			else
				write_token(ms, ptr, wlen, scp);
		}
		ptr += wlen;
		i += wlen;
	}
}
