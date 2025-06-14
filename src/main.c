/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:37:18 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/14 11:19:37 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

int main(int ac, char **av, char **envp)
{
	t_env	env;
	(void)ac,(void)av, (void)envp;

	init_env(&env, (char*[]){"envp", 0});
	bi_export(6, (char*[]){"env", "a", "a=", "a-=", "0a=", "_a=", 0}, &env, (int []){1, 1}, "caca");
	printf("\n\n");
	bi_export(1, 0, &env, (int []){1,1}, "caca");
	free_env(&env);
}
