/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:33 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 21:45:44 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_without_quote(char *str)
{
	char	*new_str;
	char	quote;
	int		i;

	if (!str || !*str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (false);
	i = 0;
	while (*str)
	{
		while (*str && *str != '\'' && *str != '"')
			new_str[i++] = *(str++);
		if (!*str)
			break ;
		quote = *(str++);
		while (*str != quote)
			new_str[i++] = *(str++);
		str++;
	}
	new_str[i] = 0;
	return (new_str);
}

static bool	update_lst(t_snippet **head, t_snippet **s, void *new_lst)
{
	void		*ptr;

	ptr = (*s)->next;
	if (new_lst)
		insert_snip(*s, new_lst);
	pop_snip(head, *s);
	*s = ptr;
	return (true);
}

static bool	replace(t_snippet **head, t_snippet **s, t_hash_table *t, bool *b)
{
	t_pair		*pair;
	t_snippet	*new_lst;

	pair = get_pair(t, (*s)->ptr, ft_strlen((*s)->ptr));
	if (!pair)
	{
		*b = true;
		*s = (*s)->next;
		return (true);
	}
	if (!pair->value || !*pass_whitespace(pair->value))
		return (update_lst(head, s, NULL));
	*b = false;
	new_lst = lexer(pair->value);
	if (!new_lst)
		return (false);
	return (update_lst(head, s, new_lst));
}

bool	replace_aliases(t_snippet **head, t_hash_table *table)
{
	t_snippet	*lst;
	bool		tmp;
	int			p;

	p = -1;
	lst = *head;
	tmp = false;
	while (lst)
	{
		if (lst->token == word && (!tmp || is_cntl_op(p) || p == open_par)
			&& !is_redir(p))
		{
			if (!replace(head, &lst, table, &tmp))
				return (false);
		}
		else
		{
			p = lst->token;
			lst = lst->next;
		}
	}
	return (true);
}
