# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 14:35:37 by ysetiawa          #+#    #+#              #
#    Updated: 2024/11/16 17:59:34 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = philo

CC              = cc
CFLAGS          = -Wall -Werror -Wextra -g -fsanitize=thread
RM              = rm -f

SRCS            = philo.c ft_libft.c init.c utils.c monitor.c simulation.c

OBJS            = $(SRCS:.c=.o)

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
