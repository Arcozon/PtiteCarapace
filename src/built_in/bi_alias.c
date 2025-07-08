/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:12:25 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 19:32:09 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "arcoms.h"

int	show_aliases(t_hash_table *table, int fdout)
{
	int		i;
	t_pair	*ptr;

	i = 0;
	while (i < TABLE_SIZE)
	{
		ptr = table->bucket[i];
		while (ptr)
		{
			ga_fprintf(fdout, "%s='%s'\n", ptr->key, ptr->value);
			ptr = ptr->next;
		}
		i++;
	}
	return (0);
}

int	len_before_eq(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	bi_alias(int ac, char **av, int fds[2], t_ms *ms)
{
	int		i;
	int		ret;
	char	*dup;
	t_pair	*new;

	if (ac == 1)
		return (show_aliases(&ms->table, fds[PIPE_WRITE]));
	i = 0;
	while (++i < ac)
	{
		ret = check_alias_chars(av[i]);
		if (ret)
		{
			ga_fprintf(2, "%s: alias: `", ms->pname);
			write(2, av[i], len_before_eq(av[i]));
			if (ret == 1)
				ga_fprintf(2, "': invalid alias name\n");
			if (ret == 2)
				ga_fprintf(2, "': invalid arguments\n");
			continue ;
		}
		dup = ft_strdup(av[i]);
		if (!dup)
			return (1);
		new = create_pair(dup);
		if (!new)
			return (free(dup), 1);
		set_pair(&ms->table, new);
	}
	return (0);
	(void)ac;
}
