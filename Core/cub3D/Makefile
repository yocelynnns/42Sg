# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 15:03:00 by yocelynnns        #+#    #+#              #
#    Updated: 2025/05/25 19:14:29 by ysetiawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               CONFIGURATION                                  #
# **************************************************************************** #

NAME            = cub3D
NAME_BONUS      = cub3D_bonus

CC              = cc
CFLAGS          = -Wall -Wextra -Werror
RM              = rm -f

# Directories
SRC_DIR         = src
BONUS_DIR       = bonus
INC_DIR         = inc
BONUS_INC_DIR   = inc_bonus
LIBFT_PATH      = libft
MLX_DIR         = minilibx-linux

# Libraries
LIBFT           = $(LIBFT_PATH)/libft.a
MLX_BUILD       = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS       = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Includes
INCLUDES        = -I$(INC_DIR) -I$(LIBFT_PATH)
BONUS_INCLUDES  = -I$(BONUS_INC_DIR) -I$(LIBFT_PATH)

# Source Files
SRCS = \
	$(SRC_DIR)/free_n_err.c \
	$(SRC_DIR)/inits.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/map_check.c \
	$(SRC_DIR)/map_check2.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/direction_updates.c \
	$(SRC_DIR)/ft_hooks.c \
	$(SRC_DIR)/helper.c \
	$(SRC_DIR)/location_updates.c \
	$(SRC_DIR)/map_helper.c \
	$(SRC_DIR)/map_helper3.c \
	$(SRC_DIR)/parse_textures.c \
	$(SRC_DIR)/parse_textures3.c \
	$(SRC_DIR)/parse_textures4.c \
	$(SRC_DIR)/render_helper.c \
	$(SRC_DIR)/draw_render.c \
	$(SRC_DIR)/inits2.c \
	$(SRC_DIR)/map_helper2.c \
	$(SRC_DIR)/parse_textures2.c

BONUS_SRCS = \
	$(BONUS_DIR)/free_n_err_bonus.c \
	$(BONUS_DIR)/free_n_err1_bonus.c \
	$(BONUS_DIR)/inits_bonus.c \
	$(BONUS_DIR)/inits2_bonus.c \
	$(BONUS_DIR)/main_bonus.c \
	$(BONUS_DIR)/map_check_bonus.c \
	$(BONUS_DIR)/map_check2_bonus.c \
	$(BONUS_DIR)/render_bonus.c \
	$(BONUS_DIR)/direction_updates_bonus.c \
	$(BONUS_DIR)/ft_hooks_bonus.c \
	$(BONUS_DIR)/hook_door_bonus.c \
	$(BONUS_DIR)/helper_bonus.c \
	$(BONUS_DIR)/location_updates_bonus.c \
	$(BONUS_DIR)/map_helper_bonus.c \
	$(BONUS_DIR)/map_helper2_bonus.c \
	$(BONUS_DIR)/map_helper3_bonus.c \
	$(BONUS_DIR)/parse_textures_bonus.c \
	$(BONUS_DIR)/parse_textures2_bonus.c \
	$(BONUS_DIR)/parse_textures3_bonus.c \
	$(BONUS_DIR)/parse_textures4_bonus.c \
	$(BONUS_DIR)/parse_textures5_bonus.c \
	$(BONUS_DIR)/render_helper_bonus.c \
	$(BONUS_DIR)/render_helper_2_bonus.c \
	$(BONUS_DIR)/render_helper_3_bonus.c \
	$(BONUS_DIR)/draw_minimap_bonus.c \
	$(BONUS_DIR)/draw_render_bonus.c \
	$(BONUS_DIR)/locate_door_bonus.c

# Object Files
OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(BONUS_SRCS:.c=.o)

# **************************************************************************** #
#                               BUILD TARGETS                                  #
# **************************************************************************** #

all: $(LIBFT) $(MLX_BUILD) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

bonus: $(LIBFT) $(MLX_BUILD) $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)

# Compile .o files with includes
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# For bonus .o files
$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(MLX_BUILD):
	@make -C $(MLX_DIR)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus

# NAME            = cub3D
# NAME_BONUS      = cub3D_bonus

# INC_DIR             = inc/
# SRC_DIR         = src/

# CC              = cc
# CFLAGS          = -Wall -Werror -Wextra
# RM              = rm -f

# BONUS_DIR       = bonus/
# BONUS_INC       = inc_bonus/

# LIBFT_PATH      = libft
# LIBFT           = $(LIBFT_PATH)/libft.a

# MLX_DIR         = ./minilibx-linux
# MLX_LIB         = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
# MLX_BUILD       = $(MLX_DIR)/libmlx_Linux.a

# SRCS            = $(SRC_DIR)free_n_err.c \
# 				  $(SRC_DIR)inits.c \
# 				  $(SRC_DIR)main.c \
# 				  $(SRC_DIR)map_check.c \
# 				  $(SRC_DIR)map_check2.c \
# 				  $(SRC_DIR)render.c \
# 				  $(SRC_DIR)direction_updates.c \
# 				  $(SRC_DIR)ft_hooks.c \
# 				  $(SRC_DIR)helper.c \
# 				  $(SRC_DIR)location_updates.c \
# 				  $(SRC_DIR)map_helper.c \
# 				  $(SRC_DIR)map_helper3.c \
# 				  $(SRC_DIR)parse_textures.c \
# 				  $(SRC_DIR)parse_textures3.c \
# 				  $(SRC_DIR)parse_textures4.c \
# 				  $(SRC_DIR)render_helper.c \
# 				  $(SRC_DIR)draw_render.c \
# 				  $(SRC_DIR)inits2.c \
# 				  $(SRC_DIR)map_helper2.c \
# 				  $(SRC_DIR)parse_textures2.c 

# BONUS_SRCS      = \
# 				  $(BONUS_DIR)free_n_err_bonus.c \
# 				  $(BONUS_DIR)free_n_err1_bonus.c \
# 				  $(BONUS_DIR)inits_bonus.c \
# 				  $(BONUS_DIR)inits2_bonus.c \
# 				  $(BONUS_DIR)main_bonus.c \
# 				  $(BONUS_DIR)map_check_bonus.c \
# 				  $(BONUS_DIR)map_check2_bonus.c \
# 				  $(BONUS_DIR)render_bonus.c \
# 				  $(BONUS_DIR)direction_updates_bonus.c \
# 				  $(BONUS_DIR)ft_hooks_bonus.c \
# 				  $(BONUS_DIR)hook_door_bonus.c \
# 				  $(BONUS_DIR)helper_bonus.c \
# 				  $(BONUS_DIR)location_updates_bonus.c \
# 				  $(BONUS_DIR)map_helper_bonus.c \
# 				  $(BONUS_DIR)map_helper2_bonus.c \
# 				  $(BONUS_DIR)map_helper3_bonus.c \
# 				  $(BONUS_DIR)parse_textures_bonus.c \
# 				  $(BONUS_DIR)parse_textures2_bonus.c \
# 				  $(BONUS_DIR)parse_textures3_bonus.c \
# 				  $(BONUS_DIR)parse_textures4_bonus.c \
# 				  $(BONUS_DIR)parse_textures5_bonus.c \
# 				  $(BONUS_DIR)render_helper_bonus.c \
# 				  $(BONUS_DIR)render_helper_2_bonus.c \
# 				  $(BONUS_DIR)render_helper_3_bonus.c \
# 				  $(BONUS_DIR)draw_minimap_bonus.c \
# 				  $(BONUS_DIR)draw_render_bonus.c \
# 				  $(BONUS_DIR)locate_door_bonus.c 
				  
# OBJS            = $(SRCS:.c=.o)
# OBJS_BONUS      = $(BONUS_SRCS:.c=.o)

# INCLUDES        = -I$(INC_DIR)
# BONUS_INCLUDES  = -I$(BONUS_INC)

# all: $(LIBFT) $(MLX_BUILD) $(NAME)

# bonus: $(NAME_BONUS)

# $(LIBFT):
# 	make -C $(LIBFT_PATH)

# $(MLX_BUILD):
# 	$(MAKE) -C $(MLX_DIR)

# $(NAME): $(OBJS) $(LIBFT) $(MLX_BUILD)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_LIB) $(LIBFT)

# $(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_BUILD)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) $(MLX_LIB) $(LIBFT)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJS) $(OBJS_BONUS)
# 	make -C $(LIBFT_PATH) clean
# 	make -C $(MLX_DIR) clean

# fclean: clean
# 	$(RM) $(NAME) $(NAME_BONUS)
# 	make -C $(LIBFT_PATH) fclean

# re: fclean all

# .PHONY: all clean fclean re bonus
