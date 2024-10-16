# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 14:35:37 by ysetiawa          #+#    #+#              #
#    Updated: 2024/10/15 16:26:14 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = pipex

CC              = cc
CFLAGS          = -Wall -Werror -Wextra
RM              = rm -f

SRCS            = pipex.c utils.c ft_libft.c ft_split.c

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