/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:39:22 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/04 12:23:02 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_closing_bracket(char *opening_bracket)
{
	char	*ptr;
	int		i;

	ptr = opening_bracket;
	i = 1;
	while (ptr[i] && ptr[i] != ')')
	{
		if (ptr[i] == '\'' || ptr[i] == '"')
			i += closing_match(ptr + i);
		else if (ptr[i] == '(')
			i += find_closing_bracket(ptr + i);
		i++;
	}
	return (i);
}

int	closing_match(char *ptr)
{
	char	*tmp;

	if (*ptr == '\'' || *ptr == '"')
	{
		tmp = ft_strchr(ptr + 1, *ptr);
		if (!tmp)
			return (0);
		return (tmp - ptr);
	}
	return (find_closing_bracket(ptr));
}

int	word_len(char *str, bool (*is_sep)(char ), int len)
{
	int		i;

	i = 0;
	while (i < len && str[i])
	{
		//i += pass_whitespace(str + i) - (str + i);
		if (!i && is_sep(str[i]))
		{
			if (*str == '(' || *str == ')' || *str == ';')
				return (1);
			if (*str == '<' || *str == '>' || *str == '|' || *str == '&')
				return ((int []){1, 2}[str[0] == str[1]]);
			i++;
		}
		while (str[i] && !is_sep(str[i]) && !ft_strchr(OPENER, str[i]))
			i++;
		if (!str[i] || is_sep(str[i]) || (is_sep(str[i]) && *str == '$'))
			return (i);
		if (!ft_strchr(str + i + 1, str[i]))
			return (len);
		i += closing_match(str + i) + 1;
	}
	return (i);
}

int	dollar_len(char *str)
{
	int	i;

	if (!str || *str != '$')
		return (0);
	i = 1;
	if (str[1] == '?' || str[1] == '$')
		return (2);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

int	arc_is_var_name(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

int  len_var_name(char *str)
{
	int  len;

	len = 0;
	if (str[len] == '?')
		return (1);
	if (str[len] >= '0' && str[len] <= '9')
			return (0);
	while (arc_is_var_name(str[len]))
			++len;
	return (len);
}

int  len_dollar(char *str, int *i, char **env)
{
	int  len_vname;
	int  len_vcontent;

	++*i;
	len_vname = len_var_name(str + *i);
	if (!len_vname)
			return (1);
	len_vcontent = 0;
	while (*env)
	{
		if (!ge_strncmp_weq(str + *i, *env, len_vname))
		{
			len_vcontent = ft_strlen(*env + len_vname + 1);
			break ;
		}
		++env;
	}
	*i += len_vname;
	return (len_vcontent);
}

// int arc_get_wlen(char *ptr, int lim, char **env)
// {	
// 	int	len;
// 	int	i;

// 	len = 0;
// 	i = 0;
// 	while (ptr[i])
// 	{
// 		if (ptr[i] == '\'')
// 		{
// 			++i;
// 			while (ptr[i] && ptr[i] != '\'')
// 			{
// 				++len;
// 				++i;
// 			}
// 			++i;
// 		}
// 		if (ptr[i] == '\"')
// 		{
// 			++i;
// 			while (ptr[i] && ptr[i] != '\"')
// 			{
// 				if (ptr[i] == '$')
// 					len += len_dollar(ptr,  &i, env);
// 				else
// 				{
// 					++len;
// 					++i;
// 				}
// 			}
// 			++i;
// 		}
// 		if (ptr[i] == '$')
// 			len += len_dollar(ptr,  &i, env);
// 		else
// 		{
// 			++len;
// 			++i;
// 		}
// 	}
// 	fprintf(stderr, "-- [%d] %.*s\n", len, i, ptr);
// 	return (len);
// 	(void)lim;
// }
bool	dollar_sep_quote(char c);

int	get_wlen(char *ptr, int len)
{
	int	wlen;
	if (*ptr == '$')
		wlen = dollar_len(ptr);
	else if (*ptr == '\'' || *ptr == '"')
		wlen = closing_match(ptr) + 1;
	else
		wlen = word_len(ptr, dollar_sep_quote, len);
	return (wlen);
}
