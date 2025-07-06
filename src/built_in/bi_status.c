/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:02:27 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/06 15:25:46 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

static void	status_atoi(char *str, int *to_store)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	if (!ft_isdigit(str[i]))
		return ;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	*to_store = res * sign;
}

int	bi_status(int ac, char **av, int fds[2], t_ms *ms)
{
	int	rvalue;

	rvalue = ms->status;
	if (ac >= 2)
		status_atoi(av[1], &rvalue);
	return (rvalue);
	(void)fds;
}
