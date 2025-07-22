/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:39:38 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/22 20:59:19 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_cp = NULL;
	map->map_w = 0;
	map->map_h = 0;
	map->map_fd = -1;
	map->no_path = NULL;
	map->so_path = NULL;
	map->ea_path = NULL;
	map->we_path = NULL;
	map->door_path = NULL;
	ft_memset(map->floor_rgb, -1, sizeof(map->floor_rgb));
	ft_memset(map->ceiling_rgb, -1, sizeof(map->ceiling_rgb));
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 0;
	map->p_count = 0;
	map->door_count = 0;
	map->doors = NULL;
	map->has_no = false;
	map->has_so = false;
	map->has_ea = false;
	map->has_we = false;
	map->has_floor = false;
	map->has_ceiling = false;
	map->has_door = false;
}

void	init_sprites(t_sprite *sprites)
{
	sprites->x = 0;
	sprites->y = 0;
	sprites->current_frame = 0;
}

void	init_game1(t_game *game)
{
	game->img = NULL;
	game->img_addr = NULL;
	game->bits_per_pixel = 0;
	game->line_length = 0;
	game->endian = 0;
	game->ceiling_color = 0;
	game->floor_color = 0;
	game->tex_no = NULL;
	game->tex_so = NULL;
	game->tex_we = NULL;
	game->tex_ea = NULL;
	game->tex_door = NULL;
	game->sprite_count = 0;
	game->anim_counter = 0;
	game->z_buffer = 0;
}

void	init_game(t_map *map, t_game *game, t_player *player)
{
	int	i;

	i = 0;
	while (i < SPRITE_FRAMES)
		game->tex_coin[i++] = NULL;
	game->map = map;
	game->win = NULL;
	game->win_w = 1920;
	game->win_h = 1080;
	game->p = player;
	game->move_backward = 0;
	game->move_forward = 0;
	game->move_left = 0;
	game->move_right = 0;
	game->rotate_left = 0;
	game->rotate_right = 0;
	game->mlx = NULL;
	game->player_next_to_door = 0;
	game->press_space = 0 ;
}

void	init_player(t_player *player, t_map *map)
{
	player->dir_x = -1;
	player->dir_y = -1;
	player->x = map->player_x;
	player->y = map->player_y;
	player->pln_x = -1;
	player->pln_x = -1;
}
