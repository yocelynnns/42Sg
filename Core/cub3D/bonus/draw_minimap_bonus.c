/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:08:20 by nsan              #+#    #+#             */
/*   Updated: 2025/05/25 16:32:32 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	j = 0;
	while (j < MINIMAP_SCALE)
	{
		i = 0;
		while (i < MINIMAP_SCALE)
		{
			px = x * MINIMAP_SCALE + i + MINIMAP_OFFSET_X;
			py = y * MINIMAP_SCALE + j + MINIMAP_OFFSET_Y;
			my_mlx_pixel_put(game, px, py, color);
			i++;
		}
		j++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < game->map->map_h)
	{
		x = 0;
		while (game->map->map[y][x] != '\0')
		{
			if (game->map->map[y][x] == '1')
				color = 0x888888;
			else if (game->map->map[y][x] == 'D')
				color = 0xFFA500;
			else if (game->map->map[y][x] == 'C')
				color = 0xFFFF00;
			else
				color = 0x000000;
			draw_tile(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game, int px, int py)
{
	int	i;
	int	j;

	j = -1;
	while (j <= 1)
	{
		i = -1;
		while (i <= 1)
		{
			my_mlx_pixel_put(game, px + i, py + j, 0xFF0000);
			i++;
		}
		j++;
	}
}

void	draw_direction(t_game *game, int px, int py)
{
	int	d;
	int	dir_x;
	int	dir_y;

	d = 0;
	dir_x = game->p->dir_x * 5;
	dir_y = game->p->dir_y * 5;
	while (d < 5)
	{
		my_mlx_pixel_put(game, px + dir_x * d, py + dir_y * d, 0x00FFFF);
		d++;
	}
}

void	render_minimap(t_game *game)
{
	int	player_px;
	int	player_py;

	draw_map(game);
	player_px = game->p->x * MINIMAP_SCALE + MINIMAP_OFFSET_X;
	player_py = game->p->y * MINIMAP_SCALE + MINIMAP_OFFSET_Y;
	draw_player(game, player_px, player_py);
	draw_direction(game, player_px, player_py);
}
