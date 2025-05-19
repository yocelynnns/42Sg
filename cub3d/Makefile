# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 15:03:00 by yocelynnns        #+#    #+#              #
#    Updated: 2025/05/14 17:27:25 by nsan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3d

INC             = inc/
SRC_DIR         = src/

CC              = cc
CFLAGS          = -Wall -Werror -Wextra -g -I$(INC)
RM              = rm -f

LIBFT_PATH      = libft
LIBFT           = $(LIBFT_PATH)/libft.a

MLX_DIR         = ./minilibx-linux
MLX_LIB         = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
MLX_BUILD       = $(MLX_DIR)/libmlx_Linux.a

SRCS            = $(SRC_DIR)free_n_err.c \
				  $(SRC_DIR)inits.c \
				  $(SRC_DIR)main.c \
				  $(SRC_DIR)map_check.c \
				  $(SRC_DIR)map_check2.c \
				  $(SRC_DIR)render.c \
				  $(SRC_DIR)direction_updates.c \
				  $(SRC_DIR)ft_hooks.c \
				  $(SRC_DIR)helper.c \
				  $(SRC_DIR)location_updates.c \
				  $(SRC_DIR)map_helper.c \
				  $(SRC_DIR)parse_textures.c \
				  $(SRC_DIR)render_helper.c \

OBJS            = $(SRCS:.c=.o)

all: $(LIBFT) $(MLX_BUILD) $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX_BUILD):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_BUILD)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_LIB) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
