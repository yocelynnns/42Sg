# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 14:35:37 by ysetiawa          #+#    #+#              #
#    Updated: 2024/10/23 16:31:29 by ysetiawa         ###   ########.fr        #
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

SRCS            = $(SRC_DIR)handle_error.c \
				  $(SRC_DIR)flood_fill.c \
				  $(SRC_DIR)so_long.c \
				  $(SRC_DIR)ft_libft.c \
				  $(SRC_DIR)ft_split.c \
				  $(SRC_DIR)elem_check.c \
				  $(SRC_DIR)map_check.c \
				  $(SRC_DIR)mlx_stuff.c

OBJS            = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re