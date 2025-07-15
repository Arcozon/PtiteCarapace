/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:14:22 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ms_exit(int rstatus, t_ms *ms)
{
	print_code_error(ms->errors, ms->pname);
	free_ms(ms);
	exit(rstatus);
}
