# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 14:35:37 by ysetiawa          #+#    #+#              #
#    Updated: 2024/10/25 01:04:11 by yocelynnns       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = so_long

INC             = inc/
SRC_DIR         = src/

CC              = cc
CFLAGS          = -Wall -Werror -Wextra -g -I$(INC)
RM              = rm -f

MLX_DIR         = ./minilibx-linux
MLX_LIB         = -L$(MLX_DIR) -lmlx -lX11 -lXext

PRINTF_DIR      = ft_printf
PRINTF_LIB      = $(PRINTF_DIR)/libftprintf.a

SRCS            = $(SRC_DIR)handle_error.c \
				  $(SRC_DIR)flood_fill.c \
				  $(SRC_DIR)so_long.c \
				  $(SRC_DIR)ft_libft.c \
				  $(SRC_DIR)ft_split.c \
				  $(SRC_DIR)elem_check.c \
				  $(SRC_DIR)map_check.c \
				  $(SRC_DIR)mlx_stuff.c \
				  $(SRC_DIR)movements.c \
				  $(SRC_DIR)inits.c

OBJS            = $(SRCS:.c=.o)

all: $(PRINTF_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_LIB) $(PRINTF_LIB)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re