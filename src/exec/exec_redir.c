/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:20:17 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/10 17:18:00 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void print_snippet_list(t_snippet *head);

void	next_snippet(t_snippet **snippet)
{
	t_snippet	*to_free;

	to_free = *snippet;
	if (to_free)
	{
		*snippet = to_free->next;
		free(to_free->ptr);
		free(to_free);
	}
}

uint64_t	open_redir(t_cmd *cmd, t_ms *ms)
{
	if (!cmd->redirs)
		return (NO_ERR);
	expand_snip(&cmd->redirs, cmd->redirs, ms, true);
	while (!cmd->errors && cmd->redirs)
	{
		if (cmd->redirs->token == redir_in)
			cmd->errors |= cmd_open(&(cmd->fd_in), cmd->redirs->ptr,
					O_RDONLY, ms->pname);
		else if (cmd->redirs->token == redir_out)
			cmd->errors |= cmd_open(&(cmd->fd_out), cmd->redirs->ptr,
					O_WRONLY | O_CREAT | O_TRUNC, ms->pname);
		else if (cmd->redirs->token == append)
			cmd->errors |= cmd_open(&(cmd->fd_out), cmd->redirs->ptr,
					O_WRONLY | O_CREAT | O_APPEND, ms->pname);
		next_snippet(&(cmd->redirs));
	}
	if (cmd->errors & E_OPEN)
		cmd->rstatus = 1;
	return (cmd->errors);
}
