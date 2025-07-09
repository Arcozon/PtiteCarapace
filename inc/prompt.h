/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:33:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/09 17:09:54 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "types.h"

# define PROMPT_SIZE		2056
# define RESERVED_P_SIZE	7
# define HOST_SIZE			1024
# define HOSTNAME_FILE			"/etc/hostname"

# if PROMPT_SIZE < RESERVED_P_SIZE
#  error "PROMPT_SIZE < RESERVED_P_SIZE"
# endif

# define PROMPT_CHARSET			"[]nae?\\uhHwWMsS"
# define BASE_PROMPT_FORMAT		"\\M>\\?$ "

# define PROMPT2_CHARSET		"[]ae\\lLM"
# define BASE_PROMPT2_FORMAT	">\\?$\\[\033[0m\\] "

# define COLOR_SUCCESS	"\1[1;38;2;40;170;60m\2"
# define COLOR_FAILURE	"\1[1;38;2;220;26;26m\2"

enum e_missing
{
	m_squote,
	m_dquote,
	m_par,
	m_pipe,
	m_and,
	m_or
};

struct s_mprompt1
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

struct s_mprompt2
{
	char		*format;
	uint32_t	i_format;

	uint32_t	i_res;

	const char	*c_missing;
	const char	*str_missing;
	char		*pname;
};

void	make_prompt(char prompt[PROMPT_SIZE], t_ms *ms);
void	cpy_prompt(char prompt[PROMPT_SIZE], t_mprompt1 *mprompt);

#endif
