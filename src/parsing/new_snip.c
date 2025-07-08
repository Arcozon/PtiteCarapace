/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_snip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:26:26 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/08 16:26:27 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_snippet	*new_snip(enum e_token token, char *ptr)
{
	t_snippet	*new;

	new = malloc(sizeof(t_snippet));
	if (!new)
		return (NULL);
	new->token = token;
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}
