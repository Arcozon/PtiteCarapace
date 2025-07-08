/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr_without_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:24 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 16:51:55 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_without_q(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

int	ft_strncmp_without_q(char *s_w_q, char *cmp, int len_w_q)
{
	int	i;
	int	j;

	if (!cmp && !s_w_q)
		return (0);
	if (!cmp)
		return (*s_w_q);
	if (!s_w_q)
		return (*cmp);
	i = 0;
	j = 0;
	while (s_w_q[i] && i < len_w_q - 1)
	{
		if (ft_strchr("\'\"", s_w_q[i]))
		{
			i++;
			continue ;
		}
		if (s_w_q[i] != cmp[j])
			return (s_w_q[i] - cmp[j]);
		i++;
		j++;
	}
	return ((int []){s_w_q[i] - cmp[j], 0}[ft_strchr("\'\"", s_w_q[i]) != 0]);
}

static void	set_to_zero(size_t *i, size_t *x, size_t *y)
{
	if (i)
		*i = 0;
	if (x)
		*x = 0;
	if (y)
		*y = 0;
}

char	*ft_strnstr_without_q(const char *big, const char *l, size_t len)
{
	size_t	i;
	size_t	x;
	size_t	y;

	set_to_zero(&i, &x, &y);
	if (!l || !*l)
		return ((char *)big);
	if (!big || !len)
		return (NULL);
	while (big[i + x] && x + i < len && l[x + y])
	{
		if (ft_strchr("\'\"", l[x + y]))
			y++;
		else if (big[i + x] == l[x + y])
			x++;
		else
		{
			set_to_zero(NULL, &x, &y);
			i++;
		}
	}
	if (!l[x + y] || (ft_strchr("\'\"", l[x + y]) && !l[x + y + 1]))
		return ((char *)big + i);
	return (NULL);
}
