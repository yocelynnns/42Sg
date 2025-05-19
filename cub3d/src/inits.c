/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:39:38 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/19 00:53:08 by yocelynnns       ###   ########.fr       */
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
	ft_memset(map->floor_rgb, -1, sizeof(map->floor_rgb));
	ft_memset(map->ceiling_rgb, -1, sizeof(map->ceiling_rgb));
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 0;
	map->p_count = 0;
	map->door_count = 0;
	map->doors = NULL;
}

void	init_game(t_map *map, t_game *game, t_player *player)
{
	game->map = map;
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

void    init_player(t_player *player, t_map *map)
{
	player->dir_x = -1;
	player->dir_y = -1;
	player->x = map->player_x;
	player->y = map->player_y;
	player->plane_x = -1;
	player->plane_y = -1;
}

int	init_win(t_game *game, t_map *map, t_player *player)
{
	init_player(player, map);
	init_game(map, game, player);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		printf("Error: Failed to initialize MLX\n");
		return (1);
	}
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3d");
	if (game->win == NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		printf("Error: Failed to create window\n");
		return (1);
	}
	game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	if (!game->img)
		return (printf("Error: Failed to create image\n"), 1);
	
	game->img_addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	// Convert ceiling/floor colors to int
	game->ceiling_color = (map->ceiling_rgb[0] << 16)
						| (map->ceiling_rgb[1] << 8)
						| map->ceiling_rgb[2];
	game->floor_color = (map->floor_rgb[0] << 16)
						| (map->floor_rgb[1] << 8)
						| map->floor_rgb[2];

	// Load wall textures
	int tex_w, tex_h;
	game->tex_no = mlx_xpm_file_to_image(game->mlx, map->no_path, &tex_w, &tex_h);
	if (!game->tex_no)
	{
		printf("Error: Failed to load North texture\n");
		return (1);
	}
	game->tex_so = mlx_xpm_file_to_image(game->mlx, map->so_path, &tex_w, &tex_h);
	if (!game->tex_so)
	{
		printf("Error: Failed to load South texture\n");
		return (1);
	}
	game->tex_we = mlx_xpm_file_to_image(game->mlx, map->we_path, &tex_w, &tex_h);
	if (!game->tex_we)
	{
		printf("Error: Failed to load West texture\n");
		return (1);
	}
	game->tex_ea = mlx_xpm_file_to_image(game->mlx, map->ea_path, &tex_w, &tex_h);
	if (!game->tex_ea)
	{
		printf("Error: Failed to load East texture\n");
		return (1);
	}
	game->tex_door = mlx_xpm_file_to_image(game->mlx, map->door_path, &tex_w, &tex_h);
	if (!game->tex_door)
	{
		printf("Error: Failed to load door texture\n");
		return (1);
	}

	// game->tex_opening = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &tex_w, &tex_h);
	// if (!game->tex_opening)
	// {
	// 	printf("Error: Failed to load door open texture\n");
	// 	return (1);
	// }
	return (0);
}
