/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:44:10 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 17:44:40 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# define SIG_HDOC_SET	0
# define SIG_HDOC_RESET	1

extern int	g_sig;

void	sig_exec(int sig);
void	set_sig_heredoc(void);
void	set_sig_exec(void);
void	capture_signal_hdoc(int status);

#endif
