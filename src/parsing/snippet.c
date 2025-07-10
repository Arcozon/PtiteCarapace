/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snippet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:49:29 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/04 19:08:48 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

int	expand_in_pipe(char *str, t_ms *ms, bool one_block, bool *test)
{
	int	stdout_fd;
	int	pipe_fds[2];

	stdout_fd = dup(STDOUT_FILENO);
	if (stdout_fd < 0 || pipe(pipe_fds) < 0)
		return (-1);
	if (dup2(pipe_fds[1], STDOUT_FILENO) < 0)
		return (close(stdout_fd), close(pipe_fds[0]), close(pipe_fds[1]), -1);
	*test = expand_token(str, ms, ft_strlen(str), (char)one_block);
	write(STDOUT_FILENO, "\0", 1);
	close(pipe_fds[1]);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	return (pipe_fds[0]);
}

bool	get_snips_expanded(t_snippet **new_lst, int fd, enum e_token token, bool test)
{
	char	*str;

	str = get_next_null_arco(fd);
	while (str)
	{
		if (*str && str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = 0;
		if ((*str || test) && !add_to_snip_lst(new_lst, token, str))
			return (free_snip_lst(*new_lst), false);
		str = get_next_null_arco(fd);
	}
	return (true);
}

void	pop_n_insert(t_snippet **head, t_snippet *to_expand, t_snippet *new_lst)
{
	t_snippet	*tmp;

	if (*head == to_expand)
	{
		if ((*head)->next && new_lst)
		{
			get_last_snip(new_lst)->next = (*head)->next;
			*head = new_lst;
		}
		else if ((*head)->next)
			*head = (*head)->next;
		else
			*head = new_lst;
	}
	else
	{
		tmp = *head;
		while (tmp->next != to_expand)
			tmp = tmp->next;
		tmp->next = to_expand->next;
		if (new_lst)
			insert_snip(tmp, new_lst);
	}
}

t_snippet	**get_addr_last(t_snippet **lst)
{
	while (*lst)
		lst = &((*lst)->next);
	return (lst);
}

bool	expand_snip(t_snippet **store, t_snippet *exp, t_ms *ms, bool one_blk)
{
	t_snippet	*new_lst;
	t_snippet	*tmp;
	t_snippet	*next;
	int			fd;
	bool		test;
	bool		t = false;

	new_lst = 0;
	if (!exp)
		return (true);
	while (exp)
	{
		next = exp->next;
		tmp = NULL;
		fd = expand_in_pipe(exp->ptr, ms, one_blk, &test);
		if (!get_snips_expanded(&tmp, fd, exp->token, test))
			return (close(fd), false);
		if (!t)
			t = test;
		close(fd);
		*get_addr_last(&new_lst) = tmp;
		free(exp->ptr);
		free(exp);
		exp = next;
	}
	*store = new_lst;
	return (true);
}
