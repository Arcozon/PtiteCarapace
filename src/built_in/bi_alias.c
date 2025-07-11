/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:12:25 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:33:50 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

bool	check_alias_chars(char *str, char *pname)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_strchr(FORBIDDEN_CHAR_ALIAS, str[i]))
		{
			ga_fprintf(2, "%s: alias: `%s': invalid alias name\n",
				pname, str);
			return (false);
		}
		i++;
	}
	if (str[i] != '=' || is_statement_open(str + i + 1))
	{
		ga_fprintf(2, "%s: alias: `%s': invalid alias name\n", pname, str);
		return (false);
	}
	return (true);
}

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
	int		error;
	int		i;
	char	*dup;
	t_pair	*new;

	error = 0;
	if (ac == 1)
		return (show_aliases(&ms->table, fds[PIPE_WRITE]));
	i = 0;
	while (++i < ac)
	{
		if (!check_alias_chars(av[i], ms->pname))
		{
			error = 1;
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
	return (error);
}
