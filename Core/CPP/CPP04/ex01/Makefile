# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 23:49:06 by yocelynnns        #+#    #+#              #
#    Updated: 2025/04/11 01:43:11 by yocelynnns       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ex01

CPP			= c++
CPPFLAGS	= -Wall -Werror -Wextra -g -std=c++98
RM			= rm -f

SRCS		= main.cpp Animal.cpp Dog.cpp Cat.cpp Brain.cpp
OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re