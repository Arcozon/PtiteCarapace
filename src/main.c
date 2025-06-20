/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:37:18 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/21 18:05:25 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int main(int ac, char **av, char **envp)
{
	t_env	__attribute__((cleanup(free_env)))	env;
	init_env(&env, envp);
	(void)ac,(void)av, (void)envp;
}
