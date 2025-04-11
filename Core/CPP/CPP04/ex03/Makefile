# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 23:49:06 by yocelynnns        #+#    #+#              #
#    Updated: 2025/04/11 23:58:20 by yocelynnns       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ex03

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinc

SRC_DIR = src
SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/AMateria.cpp \
      $(SRC_DIR)/Ice.cpp \
      $(SRC_DIR)/Cure.cpp \
      $(SRC_DIR)/Character.cpp \
      $(SRC_DIR)/MateriaSource.cpp

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
