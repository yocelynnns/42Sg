# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 19:29:40 by yocelynnns        #+#    #+#              #
#    Updated: 2025/06/18 14:28:19 by yocelynnns       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test

CPP			= c++
CPPFLAGS	= -Wall -Werror -Wextra -std=c++98
RM			= rm -f

SRCS		= main.cpp bigint.cpp
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
