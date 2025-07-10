/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:24:14 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/10 18:09:22 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	prompt2_handle_bslash(char prompt[PROMPT_SIZE], t_mprompt2 *mprompt)
{
	const char	mode = mprompt->format[++mprompt->i_format];

	if (mode == '[')
		strstopcpy_prompt2(prompt, mprompt, "\1", 0);
	else if (mode == ']')
		strstopcpy_prompt2(prompt, mprompt, "\2", 0);
	else if (mode == '\\')
		strstopcpy_prompt2(prompt, mprompt, "\\", 0);
	else if (mode == 'e')
		strstopcpy_prompt2(prompt, mprompt, "\1\033", 0);
	else if (mode == 'a')
		strstopcpy_prompt2(prompt, mprompt, "\a", 0);
	else if (mode == 'o')
		strstopcpy_prompt2(prompt, mprompt, mprompt->c_missing, 0);
	else if (mode == 'O')
		strstopcpy_prompt2(prompt, mprompt, mprompt->str_missing, 0);
	else if (mode == 'l')
		putnbcpy_prompt2(prompt, mprompt, mprompt->line);
	else if (mode == 'M')
		strstopcpy_prompt2(prompt, mprompt, mprompt->pname, 0);
	if (ft_strchr(PROMPT2_CHARSET, (int)mode))
		++mprompt->i_format;
}

void	cpy_prompt2(char prompt[PROMPT_SIZE], t_mprompt2 *mprompt)
{
	while (mprompt->i_res < PROMPT_SIZE - RESERVED_P_SIZE
		&& mprompt->format[mprompt->i_format])
	{
		if (mprompt->format[mprompt->i_format] == '\\')
			prompt2_handle_bslash(prompt, mprompt);
		else
		{
			prompt[mprompt->i_res] = mprompt->format[mprompt->i_format];
			++mprompt->i_res;
			++mprompt->i_format;
		}
	}
	strstopcpy_prompt2(prompt, mprompt, "\1\033[0m\2", 0);
	prompt[mprompt->i_res] = 0;
}

void	fill_mprompt2(t_mprompt2 *mprompt, t_ms *ms,
	enum e_missing missing, uint32_t line)
{
	static char	*missing_str[] = {"squote", "dquote", " par  ",
		" pipe ", " and  ", "  or  "};
	static char	*missing_char[] = {" '", " \"", " (", " |", "&&", "||"};

	if (missing >= 0 && missing <= 5)
	{
		mprompt->c_missing = missing_char[missing];
		mprompt->str_missing = missing_str[missing];
	}
	else
		ga_fprintf(2, "tf %d\n", missing);
	mprompt->pname = ms->pname;
	mprompt->format = find_content_var(PROMPT2_FORMAT_VNAME, ms->env.tab);
	mprompt->line = line;
}

void	make_prompt2(char prompt2[PROMPT_SIZE],
	t_ms *ms, enum e_missing missing, uint32_t line)
{
	t_mprompt2	m_prompt;

	ft_bzero(prompt2, PROMPT_SIZE);
	ft_bzero(&m_prompt, sizeof(m_prompt));
	fill_mprompt2(&m_prompt, ms, missing, line);
	if (!m_prompt.format)
		m_prompt.format = BASE_PROMPT2_FORMAT;
	cpy_prompt2(prompt2, &m_prompt);
}
