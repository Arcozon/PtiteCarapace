/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:49:39 by malfwa            #+#    #+#             */
/*   Updated: 2025/06/23 09:55:38 by malfwa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <dirent.h>

t_list	*get_a_file(const char *name)
{
	t_list	*lst;
	char	*dup;

	dup = ft_strdup(name);
	if (!dup)
		return (NULL);
	lst = ft_lstnew(dup);
	if (!lst)
		return (free(dup), NULL);
	return (lst);
}

t_list	*get_all_files(void)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*head;
	t_list			*lst;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	file = readdir(dir);
	head = NULL;
	while (file)
	{
		if (!ft_strcmp(file->d_name, ".") || !ft_strcmp(file->d_name, ".."))
		{
			file = readdir(dir);
			continue ;
		}
		lst = get_a_file(file->d_name);
		if (!lst)
			return (ft_lstclear(&head, free), closedir(dir), NULL);
		ft_lstadd_back(&head, lst);
		file = readdir(dir);
	}
	return (ft_lstsort(head), closedir(dir), head);
}

void	take_off_hidden_files(t_list **head)
{
	t_list	*lst;
	t_list	*next;

	if (!head || !*head)
		return ;
	lst = *head;
	while (lst)
	{
		next = lst->next;
		if (*(char *)lst->content == '.')
			ft_lstdelpop(head, lst, free);
		lst = next;
	}
}

int	ft_strlen_without_quote(char *str)
{
	int	i;
	int len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

int	ft_strncmp_without_quote(char *str_w_quote, char *cmp, int len_w_quote)
{
	int	i;
	int	j;

	if (!cmp && !str_w_quote)
		return (0);
	if (!cmp)
		return (*str_w_quote);
	if (!str_w_quote)
		return (*cmp);
	i = 0;
	j = 0;
	while (str_w_quote[i] && i < len_w_quote - 1)
	{
		if (ft_strchr("\'\"", str_w_quote[i]))
		{
			i++;
			continue ;
		}
		if (str_w_quote[i] != cmp[j])
			return (str_w_quote[i] - cmp[j]);
		i++;
		j++;
	}
	if (ft_strchr("\'\"", str_w_quote[i]))
		return (0);
	return (str_w_quote[i] - cmp[j]);
}

char    *ft_strnstr_without_quote(const char *big, const char *little, size_t len)
{
	size_t  i;
	size_t  x;
	size_t	y;

	i = 0;
	x = 0;
	y = 0;
	if (!little || !*little)
		return ((char *)big);
	if (!big || !len)
		return (NULL);
	while (big[i + x] && x + i < len && little[x + y])
	{
		if (ft_strchr("\'\"", little[x + y]))
			y++;
		else if (big[i + x] == little[x + y])
			x++;
		else
		{
			y = 0;
			x = 0;
			i++;
		}
	}
	if (!little[x + y] || (ft_strchr("\'\"", little[x + y]) && !little[x + y + 1]))
		return ((char *)big + i);
	return (NULL);
}

bool	check_pattern(char *str, char **patterns, char *raw_pattern)
{
	int	i;

	i = 0;
	if (*str == '.' && *raw_pattern != '.')
		return (false);
	if (*raw_pattern != '*')
	{
		if (ft_strncmp_without_quote(*patterns, str, ft_strlen(*patterns)))
			return (false);
		str += ft_strlen_without_quote(*patterns);
		i++;
	}
	while (patterns[i])
	{
		str = ft_strnstr_without_quote(str, patterns[i], ft_strlen(str));
		if (!str)
			return (false);
		str += ft_strlen_without_quote(patterns[i]);
		i++;
	}
	if (raw_pattern[ft_strlen(raw_pattern) - 1] != '*' && *str)
		return (false);
	return (true);
}

void	pop_non_matching_files(t_list **head, char **patterns, char *raw_p)
{
	t_list	*lst;
	t_list	*next;

	lst = *head;
	while (lst)
	{
		next = lst->next;
		if (!check_pattern(lst->content, patterns, raw_p))
			ft_lstdelpop(head, lst, free);
		lst = next;
	}
}
