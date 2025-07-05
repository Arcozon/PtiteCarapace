/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arco_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:59:15 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/05 10:58:35 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	fill_prompt_pwd(t_aprompt *mprompt, char **env)
{
	const char	*home_cont = find_content_var(HOME_VNAME, env);
	uint32_t	len_home;

	len_home = 0;
	if (home_cont)
		len_home = ft_strlen(home_cont);
	mprompt->pwd = getcwd(0, 0);
	if (mprompt->pwd)
	{
		mprompt->pwd_tilde = mprompt->pwd;
		if (len_home && !ft_strncmp(mprompt->pwd_tilde, home_cont, len_home))
		{
			mprompt->pwd_tilde += len_home - 1;
			mprompt->pwd_tilde[0] = '~';
		}
		mprompt->pwd_tilde_base = mprompt->pwd_tilde;
		mprompt->pwd_tilde_base += findslash(mprompt->pwd_tilde);
	}
}

void	fill_prompt_host(t_aprompt *mprompt)
{
	int	fdhost;
	int	i;

	fdhost = open(HOSTNAME_FILE, O_RDONLY);
	if (fdhost < 0)
		return ;
	read(fdhost, mprompt->hostname, HOST_SIZE);
	i = 0;
	while (mprompt->hostname[i])
	{
		if (ge_isspace(mprompt->hostname[i]))
		{
			mprompt->hostname[i] = 0;
			break ;
		}
		++i;
	}
	close(fdhost);
}

void	fill_mprompt(t_aprompt *mprompt, int status, char **env)
{

	mprompt->status = (status != 0);
	mprompt->format = find_content_var(PROMPT_FORMAT_VNAME, env);
	fill_prompt_pwd(mprompt, env);
	fill_prompt_host(mprompt);
	mprompt->user = find_content_var(USER_VNAME, env);
}

void	strstopcpy_prompt(char prompt[PROMPT_SIZE + 1], t_aprompt *mprompt,
	char *tocpy, char stop)
{
	uint32_t	i;

	if (!tocpy)
		return ;
	i = 0;
	while (mprompt->i_res < PROMPT_SIZE && tocpy[i] && tocpy[i] != stop)
	{
		prompt[mprompt->i_res] = tocpy[i];
		++mprompt->i_res;
		++i;
	}
}
void	prompt_handle_bslash(char prompt[PROMPT_SIZE + 1], t_aprompt *mprompt)
{
	const char	mode = mprompt->format[mprompt->i_format + 1];

	++mprompt->i_format;
	if (mode == '[')
		strstopcpy_prompt(prompt, mprompt, "\1", 0);
	else if (mode == ']')
		strstopcpy_prompt(prompt, mprompt, "\2", 0);
	else if (mode == '\\')
		strstopcpy_prompt(prompt, mprompt, "\\", 0);
	else if (mode == 'u')
		strstopcpy_prompt(prompt, mprompt, mprompt->user, 0);
	else if (mode == 'h')
		strstopcpy_prompt(prompt, mprompt, mprompt->hostname, '.');
	else if (mode == 'H')
		strstopcpy_prompt(prompt, mprompt, mprompt->hostname, 0);
	else if (mode == 'w')
		strstopcpy_prompt(prompt, mprompt, mprompt->pwd_tilde, 0);
	else if (mode == 'W')
		strstopcpy_prompt(prompt, mprompt, mprompt->pwd_tilde_base, 0);
	else if (mode == '?')
		strstopcpy_prompt(prompt, mprompt,
			(char *[]){COLOR_FAILURE,
			COLOR_SUCCESS}[mprompt->status == 0], 0);
	if (ft_strchr(PROMPT_CHARSET_ARCO, (int)mode))
		++mprompt->i_format;
}

void	cpy_prompt(char prompt[PROMPT_SIZE + 1], t_aprompt *mprompt)
{
	while (mprompt->i_res < PROMPT_SIZE && mprompt->format[mprompt->i_format])
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

void	make_prompt(char prompt[PROMPT_SIZE + 1], uint8_t status, char **env)
{
	t_aprompt	m_prompt;

	ft_bzero(prompt, PROMPT_SIZE + 1);
	ft_bzero(&m_prompt, sizeof(m_prompt));
	ft_bzero(m_prompt.hostname, HOST_SIZE);
	fill_mprompt(&m_prompt, status, env);
	if (!m_prompt.format)
		m_prompt.format = BASE_PROMPT_FORMAT;
	cpy_prompt(prompt, &m_prompt);
	free(m_prompt.pwd);
}

void	make_prompt(char prompt[PROMPT_SIZE + 1], uint8_t status, char **env)
{
	t_aprompt	m_prompt;

	ft_bzero(prompt, PROMPT_SIZE + 1);
	ft_bzero(&m_prompt, sizeof(m_prompt));
	ft_bzero(m_prompt.hostname, HOST_SIZE);
	fill_mprompt(&m_prompt, status, env);
	if (!m_prompt.format)
		m_prompt.format = BASE_PROMPT_FORMAT;
	cpy_prompt(prompt, &m_prompt);
	free(m_prompt.pwd);
}
