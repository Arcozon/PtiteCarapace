/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:35:29 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 12:55:40 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	free_env(t_env *env)
{
	uint64_t	i;

	i = 0;
	if (env->tab)
		while (env->tab[i])
			free(env->tab[i++]);
	free(env->tab);
	env->tab = 0;
}

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
	if (cmd->argv_cmd && cmd->path_exe != cmd->argv_cmd[0])
		free(cmd->path_exe);
	cmd->path_exe = 0;
	free_tabstr(&(cmd->argv_cmd));
	close_fd(&(cmd->fd_in));
	close_fd(&(cmd->fd_out));
	free_lexer(&(cmd->heredoc));
	free_lexer(&(cmd->redirs));
	free_lexer(&(cmd->sn_argv));
	close_fd(&(cmd->fd_in));
	close_fd(&(cmd->fd_out));
	cmd->pid = 0;
}

void	free_node(t_base **pnode)
{
	t_base	*node;

	node = *pnode;
	if (!node)
		return ;
	free_cmd(&(node->cmd));
	if (node->left)
		free_node(&((*pnode)->left));
	if (node->right)
		free_node(&((*pnode)->right));
	free(node);
	*pnode = 0;
}

void	free_ms(t_ms *ms)
{
	free_node(&(ms->exec_tree));
	free_env(&ms->env);
	//free_alias
	exit(ms->status);
}
