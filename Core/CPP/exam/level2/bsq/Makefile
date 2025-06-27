# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 19:29:40 by yocelynnns        #+#    #+#              #
#    Updated: 2025/06/23 17:54:05 by yocelynnns       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test

CC			= cc
CFLAGS	    = -Wall -Werror -Wextra
RM			= rm -f

SRCS		= main.c bsq.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
