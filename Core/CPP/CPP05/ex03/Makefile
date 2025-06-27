# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 15:50:21 by yocelynnns        #+#    #+#              #
#    Updated: 2025/05/30 14:21:52 by yocelynnns       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ex03

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 -Iinc -MMD -MP

SRC_DIR = src
OBJ_DIR = obj
STUFF = yard_shrubbery

SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/Bureaucrat.cpp \
      $(SRC_DIR)/AForm.cpp \
	  $(SRC_DIR)/ShrubberyCreationForm.cpp \
      $(SRC_DIR)/RobotomyRequestForm.cpp \
      $(SRC_DIR)/PresidentialPardonForm.cpp \
      $(SRC_DIR)/Intern.cpp

OBJ = $(OBJ_DIR)/main.o \
      $(OBJ_DIR)/Bureaucrat.o \
      $(OBJ_DIR)/AForm.o \
	  $(OBJ_DIR)/ShrubberyCreationForm.o \
      $(OBJ_DIR)/RobotomyRequestForm.o \
      $(OBJ_DIR)/PresidentialPardonForm.o \
      $(OBJ_DIR)/Intern.o

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
	rm -rf $(OBJ_DIR) $(STUFF)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
