/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:04:47 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 18:06:50 by malfwa           ###   ########.fr       */
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
