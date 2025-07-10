/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_missing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:59:34 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/10 11:50:32 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define MISSING_SPECIAL "|;()"

enum e_missing
{
	m_squote,
	m_dquote,
	m_par,
	m_pipe,
	m_and,
	m_or
};

int	ft_is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (*s2);
	if (!s2)
		return (*s1);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	a;

	a = (char)c;
	str = (char *)s;
	i = 0;
	if (!s)
		return (NULL);
	while (str[i])
	{
		if (str[i] == a)
			return (&(str[i]));
		i++;
	}
	if (a == '\0')
		return (&(str[i]));
	return (NULL);
}

void	p_missing(int missing)
{
	const char *str_missing[] = {"m_squote", "m_dquote", "m_par", "m_pipe", "m_and", "m_or"};

	if (missing <= -1 || missing > 6)
		printf("Missing: None\n");
	else
		printf("Missing: %s\n", str_missing[missing]);
}

void	wc_handle_quotes(int *missing, char *str, int *i)
{
	const char	quote = str[*i];

	printf("In: %s\n", quote == '"' ? "dquote" : "squote");
	*missing = m_squote;
	if (quote == '"')
		*missing = m_dquote;
	++*i;
	while (str[*i] && str[*i] != quote)
		++*i;
	printf("[%c:%d]\n", str[*i], str[*i]);
	if (str[*i])
	{
		*missing = -1;
		++*i;
	}
}

int	what_missing(char *str)
{
	int	par_depth;
	int	missing;
	int	i;

	par_depth = 0;
	missing = -1;
	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "&&", 2))
			missing = (++i, m_and);
		else if (!ft_strncmp(&str[i], "||", 2))
			missing = (++i, m_or);
		else if (str[i] == '(')
			++par_depth;
		else if (str[i] ==')')
			--par_depth;
		else if (str[i] == '|')
			missing = m_pipe;
		else if (!ft_is_space(str[i]))
			missing = -1;
		if (str[i] == '\'' || str[i] == '"')
			wc_handle_quotes(&missing, str, &i);
		else
			++i;
	}
	p_missing(missing);
	printf("Pdepth: %d\n", par_depth);
	if (missing == -1 && par_depth > 0)
		missing = m_par;
	return (missing);
}

int main(int ac, char **av)
{
	if (ac < 2)
		p_missing(what_missing("||"));
	else
	{
		for (int i = 1; i < ac; ++i)
			p_missing(what_missing(av[i]));
	}
}
