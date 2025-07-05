/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:28:42 by gaeudes           #+#    #+#             */
/*   Updated: 2025/07/05 10:21:11 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ga_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
int	ga_fprintf(int fd,
		const char *format, ...) __attribute__((format(printf, 2, 3)));

#endif
