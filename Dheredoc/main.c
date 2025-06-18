/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:09:00 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/18 11:47:18 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int main(int ac, char **av, char **env)
{
	t_snippet	limiters = {.next = 0, .token = here_doc};

	if (ac >= 2)
		limiters.ptr = av[1];
	else
		limiters.ptr = ft_strdup("Bonjour");
	int fd = launch_heredocs(&limiters, env, 0, av[0]); 
	WAIT
	char c;
	while (read(fd, &c, 1) == 1)
		write(1, &c, 1);
}
