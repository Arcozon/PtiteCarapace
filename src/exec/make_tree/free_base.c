/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:19:18 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/19 10:35:32 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	free_lexer(t_snippet **lexer)
{
	t_snippet	*to_free;
	t_snippet	*act;

	act = *lexer;
	while (act)
	{
		to_free = act;
		act = act->next;
		free(to_free->ptr);
		free(to_free);
	}
	*lexer = 0;
}

void	free_tabstr(char ***tab)
{
	uint64_t	i;

	if (*tab)
	{
		i = 0;
		while ((*tab)[i])
		{
			free((*tab)[i]);
			++i;
		}
	}
	free(*tab);
	*tab = 0;
}

void	free_cmd(t_cmd *cmd)
{
	free_tabstr(&(cmd->argv_cmd));
	free(cmd->path_cmd);
	cmd->path_cmd = 0;
	close_fd(&(cmd->fd_in));
	close_fd(&(cmd->fd_out));
	free_lexer(&(cmd->heredoc));
	free_lexer(&(cmd->redirs));
	free_lexer(&(cmd->sn_argv));
	close_fd(&(cmd->in_pipe));
	close_fd(&(cmd->out_pipe));
	cmd->pid = 0;
}

void	free_node(t_base **pnode)
{
	t_base	*node;

	node = *pnode;
	if (!node)
		return ;
	close_fd(&(node->fd_in));
	close_fd(&(node->fd_out));
	free_cmd(&(node->cmd));
	if (node->left)
		free_node(&((*pnode)->left));
	if (node->right)
		free_node(&((*pnode)->right));
	free(node);
	*pnode = 0;
}
