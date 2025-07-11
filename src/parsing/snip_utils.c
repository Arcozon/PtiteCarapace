/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snip_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:25:53 by malfwa            #+#    #+#             */
/*   Updated: 2025/07/11 20:04:49 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arcoms.h"

t_snippet	*get_last_snip(t_snippet *lst)
{
	if (!lst)
		ft_putstr_fd("Check your code dumbass (get_last_snip)\n", 2);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	pop_snip(t_snippet **head, t_snippet *to_pop)
{
	t_snippet	*ptr;

	if (to_pop == *head)
		*head = (*head)->next;
	else
	{
		ptr = *head;
		while (ptr->next != to_pop)
			ptr = ptr->next;
		if (!ptr)
			ft_putstr_fd("Check your code dumbass (pop_snip)\n", 2);
		ptr->next = ptr->next->next;
	}
	free(to_pop->ptr);
	free(to_pop);
}

bool	add_to_snip_lst(t_snippet **head, enum e_token token, char *ptr)
{
	t_snippet	*new;

	new = new_snip(token, ptr);
	if (!new)
		return (ft_putstr_fd("Error malloc\n", 2), false);
	if (!*head)
		*head = new;
	else
		get_last_snip(*head)->next = new;
	return (true);
}

void	insert_snip(t_snippet *node, t_snippet *to_insert)
{
	if (!node)
		ft_putstr_fd("Check your code dumbass (insert_snip)\n", 2);
	get_last_snip(to_insert)->next = node->next;
	node->next = to_insert;
}

void	free_snip_lst(t_snippet *lst)
{
	void	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->ptr);
		free(lst);
		lst = tmp;
	}
}
