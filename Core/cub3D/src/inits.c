/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:39:38 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 18:10:26 by ysetiawa         ###   ########.fr       */
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
	map->has_no = false;
	map->has_so = false;
	map->has_ea = false;
	map->has_we = false;
	map->has_floor = false;
	map->has_ceiling = false;
}

void	init_game(t_map *map, t_game *game, t_player *player)
{
	game->mlx = NULL;
	game->win = NULL;
	game->win_w = 1920;
	game->win_h = 1080;
	game->move_backward = 0;
	game->move_forward = 0;
	game->move_left = 0;
	game->move_right = 0;
	game->rotate_left = 0;
	game->rotate_right = 0;
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
	game->map = map;
	game->p = player;
}

void	init_player(t_player *player, t_map *map)
{
	player->dir_x = -1;
	player->dir_y = -1;
	player->x = map->player_x;
	player->y = map->player_y;
	player->pln_x = -1;
	player->pln_y = -1;
}

// int	init_win(t_game *game, t_map *map, t_player *player)
// {
// 	init_player(player, map);
// 	init_game(map, game, player);
// 	game->mlx = mlx_init();
// 	if (game->mlx == NULL)
// 	{
// 		putstr_fd("Error: Failed to initialize MLX\n");
// 		return (1);
// 	}
// 	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3d");
// 	if (game->win == NULL)
// 	{
// 		mlx_destroy_display(game->mlx);
// 		free(game->mlx);
// 		putstr_fd("Error: Failed to create window\n");
// 		return (1);
// 	}
// 	game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
// 	if (!game->img)
// 		return (putstr_fd("Error: Failed to create image\n"), 1);

// 	game->img_addr = mlx_get_data_addr(game->img, &game->
//bits_per_pixel, &game->line_length, &game->endian);
// 	// Convert ceiling/floor colors to int
// 	game->ceiling_color = (map->ceiling_rgb[0] << 16)
// 						| (map->ceiling_rgb[1] << 8)
// 						| map->ceiling_rgb[2];
// 	game->floor_color = (map->floor_rgb[0] << 16)
// 						| (map->floor_rgb[1] << 8)
// 						| map->floor_rgb[2];

// 	// Load wall textures
// 	int tex_w, tex_h;
// 	game->tex_no = mlx_xpm_file_to_image(game->mlx,
// map->no_path, &tex_w, &tex_h);
// 	if (!game->tex_no)
// 	{
// 		putstr_fd("Error: Failed to load North texture\n");
// 		return (1);
// 	}
// 	game->tex_so = mlx_xpm_file_to_image(game->mlx,
// map->so_path, &tex_w, &tex_h);
// 	if (!game->tex_so)
// 	{
// 		putstr_fd("Error: Failed to load South texture\n");
// 		return (1);
// 	}
// 	game->tex_we = mlx_xpm_file_to_image(game->mlx, 
//map->we_path, &tex_w, &tex_h);
// 	if (!game->tex_we)
// 	{
// 		putstr_fd("Error: Failed to load West texture\n");
// 		return (1);
// 	}
// 	game->tex_ea = mlx_xpm_file_to_image(game->mlx, map->ea_path, 
//&tex_w, &tex_h);
// 	if (!game->tex_ea)
// 	{
// 		putstr_fd("Error: Failed to load East texture\n");
// 		return (1);
// 	}
// 	return (0);
// }
