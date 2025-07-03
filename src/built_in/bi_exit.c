/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:29:37 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/28 12:30:36 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

void	exit_error_numreq(char *pname, char *nb)
{
	write(2, pname, ft_strlen(pname));
	write(2, ": exit: ", 8);
	write(2, nb, ft_strlen(nb));
	write(2, ": numeric argument required\n", 28);
}

long	exit_atoi(char *str, int *valid)
{
	u_int64_t	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while (ge_isspace(str[i]))
		++i;
	if (str[i] == '-')
		sign = (++i, -1);
	else if (str[i] == '+')
		++i;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i++] - '0';
		if (res > (uint64_t)LONG_MAX + (sign == -1))
			return (*valid = 0, 2);
	}
	if (!i || !ft_isdigit(str[i - 1]) || str[i])
		return (*valid = 0, 2);
	return (res * sign);
}

int	bi_exit(int ac, char **av, int fds[2], t_ms *ms)
{
	long	rvalue;
	int		valid;

	valid = 1;
	write(2, "exit\n", 5);
	if (ac > 1)
		rvalue = exit_atoi(av[1], &valid);
	else
		rvalue = ms->status;
	if (!valid)
		exit_error_numreq(ms->pname, av[1]);
	if (ac <= 2 || !valid)
		ms_exit(rvalue, ms);
	write(2, ms->pname, ft_strlen(ms->pname));
	write(2, ": exit: too many arguments\n", 27);
	return (1);
	(void)fds;
}
