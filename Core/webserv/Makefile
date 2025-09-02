# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 16:11:07 by ysetiawa          #+#    #+#              #
#    Updated: 2025/09/02 16:42:33 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -Iinc -MMD -MP

SRC_DIR = src
OBJ_DIR = obj

SRC = $(SRC_DIR)/main.cpp \
	  $(SRC_DIR)/ConfigParser.cpp

OBJ = $(OBJ_DIR)/main.o \
	  $(OBJ_DIR)/ConfigParser.o

DEP = $(OBJ:.o=.d)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Default target
all: $(NAME)

# Link the executable
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Include dependencies if they exist
-include $(DEP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re