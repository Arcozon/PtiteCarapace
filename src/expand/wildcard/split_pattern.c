/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:33:18 by amouflet          #+#    #+#             */
/*   Updated: 2025/07/10 17:38:13 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	ft_count_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	x;
	char			quote;

	x = 0;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] != quote)
				i++;
		}
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == 0))
			x++;
	}
	return (x);
}

static void	*ft_free(char **tab)
{
	unsigned int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static int	get_len(char const *s, char c)
{
	char	quote;
	int		len;

	len = 0;
	while (s && s[len] && s[len] != c)
	{
		if (s[len] == '\'' || s[len] == '\"')
		{
			quote = s[len++];
			while (s[len] != quote)
				len++;
		}
		len++;
	}
	return (len);
}

static int	ft_fill_tab(char **tab, char const *s, unsigned int *i, char c)
{
	int		j;
	int		len;

	while (s && s[(*i)] == c && s[(*i)] != 0)
		(*i)++;
	j = 0;
	len = get_len(s + *i, c);
	*tab = malloc(sizeof(char) * (len + 1));
	if (*tab == NULL)
		return (1);
	while (j < len)
		(*tab)[j++] = s[(*i)++];
	(*tab)[j] = 0;
	while (s && s[(*i)] == c && s[(*i)] != 0)
		(*i)++;
	return (0);
}

char	**ft_split_pattern(char const *s, char c)
{
	unsigned int	count;
	unsigned int	i;
	unsigned int	x;
	char			**tab;

	count = ft_count_word(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (tab == NULL)
		return (NULL);
	tab[count] = NULL;
	i = 0;
	x = 0;
	while (s && s[i] && x != count)
	{
		if (ft_fill_tab(&(tab[x]), s, &i, c) == 1)
			return (ft_free(tab));
		x++;
	}
	return (tab);
}
