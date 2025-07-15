/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_prompt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:30:35 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/11 20:35:42 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strstopcpy_prompt2(char prompt[PROMPT_SIZE], t_mprompt2 *mprompt,
	const char *tocpy, char stop)
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

int	_10pow_log10(uint32_t nb)
{
	int	pow;

	pow = 1;
	while (nb / 10 / pow)
		pow *= 10;
	return (pow);
}

void	putnbcpy_prompt2(char prompt[PROMPT_SIZE],
	t_mprompt2 *mprompt, uint32_t line)
{
	uint32_t	pow10;

	pow10 = _10pow_log10(line);
	while (mprompt->i_res < PROMPT_SIZE - RESERVED_P_SIZE
		&& pow10)
	{
		prompt[mprompt->i_res] = (line / pow10) % 10 + '0';
		++mprompt->i_res;
		pow10 /= 10;
	}
}
