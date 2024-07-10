# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jullopez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 10:19:20 by jullopez          #+#    #+#              #
#    Updated: 2024/07/10 15:49:04 by jullopez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft-gc.a

CFLAGS = -Wall -Wextra -Werror -g

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_toupper.c ft_tolower.c \
	gc-alloc.c gc.c gc-free.c gc-utils.c \
	get_next_line.c get_next_line_utils.c

#SRC_BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstsize.c ft_lstlast.c ft_lstmap.c ft_lstnew.c

OBJS = ${SRC:.c=.o}

#OBJS_BONUS = ${SRC_BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar -rc ${NAME} ${OBJS}

#bonus: ${OBJS_BONUS}
#	ar -rc ${NAME} ${OBJS_BONUS}

clean:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
