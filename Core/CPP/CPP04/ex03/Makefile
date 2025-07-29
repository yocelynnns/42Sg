# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 23:49:06 by yocelynnns        #+#    #+#              #
#    Updated: 2025/04/14 16:11:42 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = ex03

INC      = inc/
SRC_DIR  = src/

CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I$(INC) -g
RM       = rm -f

SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/AMateria.cpp \
      $(SRC_DIR)/Ice.cpp \
      $(SRC_DIR)/Cure.cpp \
      $(SRC_DIR)/Character.cpp \
      $(SRC_DIR)/MateriaSource.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
