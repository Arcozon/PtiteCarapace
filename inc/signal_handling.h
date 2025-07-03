/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:44:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/25 11:11:28 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# define SIG_HDOC_SET	0
# define SIG_HDOC_RESET	1

# include <stdint.h>
# include "arcoms.h"

enum e_sig
{
	ROUTINE,
	EXEC,
	HEREDOC,
	DEFLT_SIG
};

extern int	g_sig;
//extern volatile sig_atomic_t g_sig;

uint8_t	uptade_sig(uint8_t	status);
void	capture_signal_hdoc(int status, t_ms *ms);
void	set_sig(enum e_sig	mode, t_ms *ms);

#endif
