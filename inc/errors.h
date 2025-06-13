/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:12:25 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/13 15:58:45 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define NO_ERR		0b0
# define E_MLC		0b1
# define E_OPEN		0b10
# define E_READ		0b100
# define E_WRITE	0b1000
# define E_FORK		0b10000
# define E_PIPE		0b100000
# define E_DUP		0b1000000

#endif
