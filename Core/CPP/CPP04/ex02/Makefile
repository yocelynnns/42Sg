# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 23:49:06 by yocelynnns        #+#    #+#              #
#    Updated: 2025/04/12 18:21:42 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ex02

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinc

SRC_DIR = src
SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/AAnimal.cpp \
      $(SRC_DIR)/Dog.cpp \
      $(SRC_DIR)/Cat.cpp 

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
