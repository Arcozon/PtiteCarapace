/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:18:21 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/05 10:20:47 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GA_FPRINTF_H
# define GA_FPRINTF_H

int	ga_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int	ga_fprintf(int fd,
		const char *format, ...) __attribute__((format(printf, 2, 3)));

#endif
