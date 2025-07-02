# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_vars.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malfwa <admoufle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 16:30:34 by malfwa            #+#    #+#              #
#    Updated: 2025/07/02 18:19:39 by malfwa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_LIBFT	=	ft_atoi.c		\
				ft_bzero.c		\
				ft_calloc.c		\
				ft_isalnum.c	\
				ft_isalpha.c	\
				ft_isascii.c	\
				ft_isdigit.c	\
				ft_isprint.c	\
				ft_itoa.c		\
				ft_memchr.c		\
				ft_memcmp.c		\
				ft_memcpy.c		\
				ft_memmove.c	\
				ft_memset.c		\
				ft_putchar_fd.c	\
				ft_putstr_fd.c	\
				ft_putendl_fd.c	\
				ft_putnbr_fd.c	\
				ft_strlcat.c	\
				ft_striteri.c	\
				ft_strjoin.c	\
				ft_strsjoin.c	\
				ft_strlcpy.c	\
				ft_strlen.c		\
				ft_split.c		\
				ft_split_set.c	\
				ft_strmapi.c	\
				ft_strdup.c		\
				ft_free_null.c	\
				ft_strncmp.c	\
				ft_strnstr.c	\
				ft_strchr.c		\
				ft_strtrim.c	\
				ft_strrchr.c	\
				ft_strval.c		\
				ft_substr.c		\
				ft_tolower.c	\
				ft_toupper.c

SRC_LBONUS	=	ft_lstnew.c			\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_front.c	\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstdelpop.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstsort.c		\
				ft_lstmap.c

OBJ_LIBFT	=	$(addprefix .build/libft/, $(SRC_LIBFT:.c=.o))

OBJ_LBONUS	=	$(addprefix .build/libft/, $(SRC_LBONUS:.c=.o))

INCLUDE_L	=	libft
