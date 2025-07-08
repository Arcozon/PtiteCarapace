/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:59:15 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/08 17:09:06 by malfwa           ###   ########.fr       */
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
		if (len_home && !ft_strncmp(mprompt->pwd_tilde, home_cont, len_home)
			&& (mprompt->pwd_tilde[len_home] == '\0'
				|| mprompt->pwd_tilde[len_home] == '/'))
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

void	fill_mprompt(t_aprompt *mprompt, t_ms *ms)
{
	mprompt->status = ms->status;
	mprompt->format = find_content_var(PROMPT_FORMAT_VNAME, ms->env.tab);
	fill_prompt_pwd(mprompt, ms->env.tab);
	fill_prompt_host(mprompt);
	mprompt->user = find_content_var(USER_VNAME, ms->env.tab);
	mprompt->pname = ms->pname;
}

void	make_prompt(char prompt[PROMPT_SIZE], t_ms *ms)
{
	t_aprompt	m_prompt;

	ft_bzero(prompt, PROMPT_SIZE);
	ft_bzero(&m_prompt, sizeof(m_prompt));
	ft_bzero(m_prompt.hostname, HOST_SIZE + 1);
	fill_mprompt(&m_prompt, ms);
	if (!m_prompt.format)
		m_prompt.format = BASE_PROMPT_FORMAT;
	cpy_prompt(prompt, &m_prompt);
	free(m_prompt.pwd);
}
