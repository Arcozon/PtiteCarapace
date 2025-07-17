/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:04:47 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/17 19:10:50 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char **env, char *var_name, int len)
{
	int	i;

	i = 0;
	while (env[i] && ge_strncmp_weq(var_name, env[i], len))
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
			return (write(STDOUT_FILENO, str, i));
		i++;
	}
	return (write(STDOUT_FILENO, str, i));
}

int	write_without_quote(char *str, int len)
{
	int		i;
	int		len_to_write;
	char	*ptr;
	int		tmp;

	if (!str)
		return (0);
	i = 0;
	tmp = 0;
	while (*str && i < len)
	{
		if (*str != '\'')
			ft_putchar_fd(*str, STDOUT_FILENO);
		else
		{
			tmp += (str++, 1);
			ptr = ft_strchr(str, '\'');
			len_to_write = ptr - str;
			i += len_to_write + 2;
			write(STDOUT_FILENO, str, len_to_write);
			str = ptr;
		}
		i += (str++, 1);
	}
	return (tmp);
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

int	expand_dquote(char *ptr, char **env, uint8_t status, int len)
{
	int		i;
	int		wlen;
	char	q;

	i = 0;
	q = 0;
	while (i < len && ptr[i])
	{
		if (ptr[i] == '$' && ptr[i + 1] != '$')
		{
			wlen = get_wlen(ptr + i, len);
			if (wlen == 1)
				write(STDOUT_FILENO, "$", 1);
			else if (wlen == 2 && !ft_strncmp("$?", ptr + i, wlen))
				ft_putnbr_fd(status, STDOUT_FILENO);
			else
				dollar_exp(expand(env, ptr + i + 1, wlen - 1), '\"', &q);
			i += wlen;
		}
		else if (ptr[i] == '$' && ptr[i + 1] == '$')
			i += write(STDOUT_FILENO, "$$", 2);
		else
			write(STDOUT_FILENO, ptr + i++, 1);
	}
	return ('\"');
}
