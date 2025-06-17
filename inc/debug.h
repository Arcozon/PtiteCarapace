/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeudes <gaeudes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:09:09 by gaeudes           #+#    #+#             */
/*   Updated: 2025/06/17 16:54:46 by gaeudes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>

# define RESET		"[0m"
# define B_BLUE		"[1;34m"
# define BLUE		"[34m"
# define GREY		"[30m"
# define GREEN		"[32m"
# define B_LYELLOW	"[1;93m"
# define B_MAJENTA	"[1;35m"
# define B_WHITE	"[1;37m"

# define BASENAME(string)		(char *)(strrchr(string, '/') ? strrchr(string, '/') + 1 : (char *)string)
# define LEN_EXT(string)		(int)(strrchr(string, '.') ? (strrchr(string, '.') - string) : strlen(string))
# define LEN_BNAMEEXT(string)	LEN_EXT(BASENAME(string))

# define DEBUG_PROMPT		B_BLUE "%.*s" GREY "[" GREEN "%d" GREY "]" RESET ":"
# define DEBUG_PROMPT_ARGS	LEN_BNAMEEXT(__FILE__), BASENAME(__FILE__), __LINE__ 

# define WAIT_PROMPT		B_MAJENTA "WAIT" B_LYELLOW "[" RESET BLUE "%.*s" GREY "(" GREEN "%d" GREY ")"  B_LYELLOW "]" RESET " "
# define WAIT_PROMPT_ARGS	LEN_BNAMEEXT(__FILE__), BASENAME(__FILE__), __LINE__ 

# define DEBUG_OFF

# ifdef DEBUG_OFF
#  define WAIT\
	{\
		char	g = 0;\
		fprintf(stderr, WAIT_PROMPT, WAIT_PROMPT_ARGS);\
		while (read(0, &g, 1) == 1 && g != '\n') ;\
	}
#  define DEBUG(s, ...)\
	{\
			fprintf(stderr, DEBUG_PROMPT" "s"\n", DEBUG_PROMPT_ARGS, ##__VA_ARGS__);\
	}

# else
#  define WAIT			{}
#  define DEBUG(s , ...)	{(void)s;}

# endif

#endif
