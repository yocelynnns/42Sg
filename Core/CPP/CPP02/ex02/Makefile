# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 20:51:03 by ysetiawa          #+#    #+#              #
#    Updated: 2025/03/26 18:54:30 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fixed

CPP			= c++
CPPFLAGS	= -Wall -Werror -Wextra -g -std=c++98
RM			= rm -f

SRCS		= main.cpp Fixed.cpp
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