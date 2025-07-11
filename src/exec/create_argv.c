/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:33:29 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 13:31:29 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

uint64_t	expand_sn_argv(t_cmd *cmd, t_ms *ms)
{
	if (!cmd->sn_argv)
		return (NO_ERR);
	ga_fprintf(2, "[%s][%s]\n", cmd->sn_argv->ptr, cmd->sn_argv->next ? cmd->sn_argv->next->ptr : 0);
	expand_snip(&cmd->sn_argv, cmd->sn_argv, ms, false);
	ga_fprintf(2, "[%s][%s]\n", cmd->sn_argv->ptr, cmd->sn_argv->next ? cmd->sn_argv->next->ptr : 0);
	replace_wildcards(&cmd->sn_argv);
	return (ms->errors);
}

uint64_t	cllc_argv(t_snippet *sn_argv, char ***p_argv)
{
	uint64_t	len;

	len = 0;
	while (sn_argv)
	{
		++len;
		sn_argv = sn_argv->next;
	}
	*p_argv = ge_calloc(sizeof(char *) * (len + 1));
	if (!*p_argv)
		return (E_MLC);
	return (NO_ERR);
}

uint64_t	create_argv(t_cmd *cmd, t_ms *ms)
{
	uint64_t	i;
	t_snippet	*to_free;

	i = 0;
	ms->errors |= expand_sn_argv(cmd, ms);
	ms->errors |= cllc_argv(cmd->sn_argv, &cmd->argv_cmd);
	if (ms->errors)
		return (ms->errors);
	while (cmd->sn_argv)
	{
		to_free = cmd->sn_argv;
		cmd->argv_cmd[i] = cmd->sn_argv->ptr;
		cmd->sn_argv = cmd->sn_argv->next;
		free(to_free);
		++i;
	}
	return (cmd->errors);
}

int	get_ac(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		++i;
	return (i);
}
