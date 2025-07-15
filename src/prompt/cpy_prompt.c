/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:11:44 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpystatus_prompt(char prompt[PROMPT_SIZE], t_mprompt1 *mprompt,
	bool left)
{
	if (mprompt->i_res < PROMPT_SIZE - RESERVED_P_SIZE)
	{
		if (mprompt->status / 100)
			prompt[mprompt->i_res] = '0' + mprompt->status / 100 % 10;
		else if (left)
			prompt[mprompt->i_res] = ' ';
		if (mprompt->status / 100 || left)
			++mprompt->i_res;
	}
	if (mprompt->i_res < PROMPT_SIZE - RESERVED_P_SIZE)
	{
		if (mprompt->status / 10)
			prompt[mprompt->i_res] = '0' + mprompt->status / 10 % 10;
		else if (left)
			prompt[mprompt->i_res] = ' ';
		if (mprompt->status / 10 || left)
			++mprompt->i_res;
	}
	if (mprompt->i_res < PROMPT_SIZE - RESERVED_P_SIZE)
	{
		prompt[mprompt->i_res] = '0' + mprompt->status % 10;
		++mprompt->i_res;
	}
}

void	strstopcpy_prompt(char prompt[PROMPT_SIZE], t_mprompt1 *mprompt,
	char *tocpy, char stop)
{
	uint32_t	i;

	if (!tocpy)
		return ;
	i = 0;
	while (mprompt->i_res < PROMPT_SIZE - RESERVED_P_SIZE
		&& tocpy[i] && tocpy[i] != stop)
	{
		prompt[mprompt->i_res] = tocpy[i];
		++mprompt->i_res;
		++i;
	}
}

void	prompt_handle_bslasgh_2(char prompt[PROMPT_SIZE],
	t_mprompt1 *mprompt, const char mode)
{
	if (mode == '[')
		strstopcpy_prompt(prompt, mprompt, "\1", 0);
	else if (mode == ']')
		strstopcpy_prompt(prompt, mprompt, "\2", 0);
	else if (mode == '\\')
		strstopcpy_prompt(prompt, mprompt, "\\", 0);
	else if (mode == 'n')
		strstopcpy_prompt(prompt, mprompt, "\n", 0);
	else if (mode == 'e')
		strstopcpy_prompt(prompt, mprompt, "\1\033", 0);
	else if (mode == 'a')
		strstopcpy_prompt(prompt, mprompt, "\a", 0);
	else if (mode == 'u')
		strstopcpy_prompt(prompt, mprompt, mprompt->user, 0);
	else if (mode == '?')
		strstopcpy_prompt(prompt, mprompt,
			(char *[]){COLOR_FAILURE,
			COLOR_SUCCESS}[mprompt->status == 0], 0);
	else if (mode == 'u')
		strstopcpy_prompt(prompt, mprompt, mprompt->user, 0);
	else if (mode == 'h')
		strstopcpy_prompt(prompt, mprompt, mprompt->hostname, '.');
	else if (mode == 'H')
		strstopcpy_prompt(prompt, mprompt, mprompt->hostname, 0);
}

void	prompt_handle_bslash(char prompt[PROMPT_SIZE], t_mprompt1 *mprompt)
{
	const char	mode = mprompt->format[++mprompt->i_format];

	prompt_handle_bslasgh_2(prompt, mprompt, mode);
	if (mode == 'w')
		strstopcpy_prompt(prompt, mprompt, mprompt->pwd_tilde, 0);
	else if (mode == 'W')
		strstopcpy_prompt(prompt, mprompt, mprompt->pwd_tilde_base, 0);
	else if (mode == 'M')
		strstopcpy_prompt(prompt, mprompt, mprompt->pname, 0);
	else if (mode == 'S')
		cpystatus_prompt(prompt, mprompt, true);
	else if (mode == 's')
		cpystatus_prompt(prompt, mprompt, false);
	if (ft_strchr(PROMPT_CHARSET, (int)mode))
		++mprompt->i_format;
}

void	cpy_prompt(char prompt[PROMPT_SIZE], t_mprompt1 *mprompt)
{
	while (mprompt->i_res < PROMPT_SIZE - RESERVED_P_SIZE
		&& mprompt->format[mprompt->i_format])
	{
		if (mprompt->format[mprompt->i_format] == '\\')
			prompt_handle_bslash(prompt, mprompt);
		else
		{
			prompt[mprompt->i_res] = mprompt->format[mprompt->i_format];
			++mprompt->i_res;
			++mprompt->i_format;
		}
	}
	strstopcpy_prompt(prompt, mprompt, "\1\033[0m\2", 0);
	prompt[mprompt->i_res] = 0;
}
