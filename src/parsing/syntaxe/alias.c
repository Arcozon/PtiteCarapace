/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 23:00:33 by malfwa            #+#    #+#             */
/*   Updated: 2025/06/22 21:10:11 by malfwa           ###   ########.fr       */
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
	char		*tmp;

	pair = get_pair(t, (*s)->ptr, ft_strlen((*s)->ptr));
	if (!pair)
	{
		*s = (*s)->next;
		return (true);
	}
	if (!pair->value || !*pass_whitespace(pair->value))
		return (update_lst(head, s, NULL));
	*b = true;
	tmp = str_without_quote(pair->value);
	if (!tmp)
		return (false);
	new_lst = lexer(tmp);
	free(tmp);
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
		if (lst->token == word && (is_cntl_op(p) || p == open_par || !tmp))
		{
			if (!replace(head, &lst, table, &tmp))
				return (false);
			if (!lst)
				break ;
		}
		else
		{
			p = lst->token;
			if (is_cntl_op(p))
				tmp = false;
			lst = lst->next;
		}
	}
	return (true);
}
