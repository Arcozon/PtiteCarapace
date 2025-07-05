/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:33:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/05 17:12:40 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "types.h"

# define PROMPT_SIZE		2056
# define RESERVED_P_SIZE	7
# define HOST_SIZE			1024

# if PROMPT_SIZE < RESERVED_P_SIZE
#  error "PROMPT_SIZE < RESERVED_P_SIZE"
# endif

# define PROMPT_CHARSET_ARCO		"[]nae?\\uhHwWMsS"
# define HOSTNAME_FILE			"/etc/hostname"
# define BASE_PROMPT_FORMAT		"minishell>\\?$\\[\033[0m\\] "
# define PROMPT_FORMAT_VNAME	"PROMPT_FORMAT"
# define HOME_VNAME				"HOME"
# define USER_VNAME				"USER"

# define COLOR_SUCCESS	"\1[1;38;2;40;170;60m\2"
# define COLOR_FAILURE	"\1[1;38;2;220;26;26m\2"

struct s_arc_prompt
{
	char		*format;
	uint32_t	i_format;
	
	uint32_t	i_res;

	char		*pwd;
	char		*pwd_tilde;
	char		*pwd_tilde_base;
	char		hostname[HOST_SIZE + 1];
	char		*user;
	char		*pname;
	uint8_t		status;
};

void	make_prompt(char prompt[PROMPT_SIZE], t_ms *ms);
void	cpy_prompt(char prompt[PROMPT_SIZE], t_aprompt *mprompt);

#endif
