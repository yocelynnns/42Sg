# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 20:25:44 by ysetiawa          #+#    #+#              #
#    Updated: 2024/09/19 21:22:16 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = push_swap

INC             = inc/
SRC_DIR         = src/

CC              = cc
CFLAGS          = -Wall -Werror -Wextra -I$(INC)  # Add -I$(INC) here to include the header directory
RM              = rm -f

COMMANDS_DIR    = $(SRC_DIR)commands/push.c \
                  $(SRC_DIR)commands/rev_rotate.c \
                  $(SRC_DIR)commands/rotate.c \
                  $(SRC_DIR)commands/swap.c

PUSH_SWAP_DIR   = $(SRC_DIR)push_swap/ft_isdigit.c \
                  $(SRC_DIR)push_swap/ft_split.c \
                  $(SRC_DIR)push_swap/handle_errors.c \
                  $(SRC_DIR)push_swap/lists.c \
                  $(SRC_DIR)push_swap/push_swap.c \
                  $(SRC_DIR)push_swap/stack_init.c \
                  $(SRC_DIR)push_swap/utils.c

SORTING_DIR     = $(SRC_DIR)sorting/process_nodes.c \
                  $(SRC_DIR)sorting/sort_stacks.c \
                  $(SRC_DIR)sorting/sorting.c

SRCS            = $(COMMANDS_DIR) $(PUSH_SWAP_DIR) $(SORTING_DIR)

OBJS            = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

