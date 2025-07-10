/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:28:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/10 17:36:29 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GA_PRINTF_H
# define GA_PRINTF_H

int	ga_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int	ga_fprintf(int fd,
		const char *format, ...) __attribute__((format(printf, 2, 3)));

#endif
