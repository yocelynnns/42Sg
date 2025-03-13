# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 20:18:59 by ysetiawa          #+#    #+#              #
#    Updated: 2025/03/13 20:37:57 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= phonebook

CPP			= c++
CPPFLAGS	= -Wall -Werror -Wextra -std=c++98
RM			= rm -f

SRCS		= main.cpp Contact.cpp PhoneBook.cpp
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