/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snip_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:28:27 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:31:23 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

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
			ptr = ptr->next;
	}
}

t_snippet	*new_snip(enum e_token token, char *ptr)
{
	t_snippet	*new;

	new = malloc(sizeof(t_snippet));
	if (!new)
		return (NULL);
	new->token = token;
	new->ptr = ptr;
	new->next = NULL;
	return (new);
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
