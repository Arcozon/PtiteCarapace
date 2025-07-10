/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:14:22 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/10 17:41:04 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arcoms.h"

void	free_ms(t_ms *ms)
{
	free_node(&(ms->exec_tree));
	free_env(&ms->env);
	if (ms->history_fd > 0)
		close(ms->history_fd);
	free(ms->prev_cmdline);
	clear_history();
	rl_clear_history();
	free_table(&ms->table);
}
