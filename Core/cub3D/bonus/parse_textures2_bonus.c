/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:55:20 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 18:45:30 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_coin_frames(t_game *game, int w, int h)
{
	int	i;

	i = 0;
	game->tex_coin[0]
		= mlx_xpm_file_to_image(game->mlx, "textures/coin.xpm", &w, &h);
	game->tex_coin[1]
		= mlx_xpm_file_to_image(game->mlx, "textures/coin2.xpm", &w, &h);
	game->tex_coin[2]
		= mlx_xpm_file_to_image(game->mlx, "textures/coin3.xpm", &w, &h);
	game->tex_coin[3]
		= mlx_xpm_file_to_image(game->mlx, "textures/coin4.xpm", &w, &h);
	while (i <= 3)
	{
		if (!game->tex_coin[i])
			return (putstr_fd("Error: Failed to load coin texture ", 2),
				printf("%d\n", i), 1);
		i++;
	}
	return (0);
}

int	load_coin_tex(t_game *game, t_map *map)
{
	int	w;
	int	h;

	game->tex_door = mlx_xpm_file_to_image(game->mlx, map->door_path, &w, &h);
	if (!game->tex_door)
		return (putstr_fd("Error: Failed to load door texture\n", 2), 1);
	game->z_buffer = malloc(sizeof(double) * game->win_w);
	if (!game->z_buffer)
		return (1);
	return (load_coin_frames(game, w, h));
}

int	load_textures(t_game *game, t_map *map)
{
	int	tex_w;
	int	tex_h;

	game->tex_no = mlx_xpm_file_to_image(game->mlx,
			map->no_path, &tex_w, &tex_h);
	if (!game->tex_no)
		return (putstr_fd("Error: Failed to load North texture\n", 2), 1);
	game->tex_so = mlx_xpm_file_to_image(game->mlx,
			map->so_path, &tex_w, &tex_h);
	if (!game->tex_so)
		return (putstr_fd("Error: Failed to load South texture\n", 2), 1);
	game->tex_we = mlx_xpm_file_to_image(game->mlx,
			map->we_path, &tex_w, &tex_h);
	if (!game->tex_we)
		return (putstr_fd("Error: Failed to load West texture\n", 2), 1);
	game->tex_ea = mlx_xpm_file_to_image(game->mlx,
			map->ea_path, &tex_w, &tex_h);
	if (!game->tex_ea)
		return (putstr_fd("Error: Failed to load East texture\n", 2), 1);
	if (load_coin_tex(game, map))
		return (1);
	return (0);
}
