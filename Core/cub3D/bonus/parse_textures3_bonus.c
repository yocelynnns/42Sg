/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:26:47 by nsan              #+#    #+#             */
/*   Updated: 2025/05/25 16:22:52 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3d");
	if (game->win == NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		putstr_fd("Error: Failed to create window\n", 2);
		return (1);
	}
	return (0);
}

int	create_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	if (!game->img)
		return (putstr_fd("Error: Failed to create image\n", 2), 1);
	game->img_addr = mlx_get_data_addr(game->img,
			&game->bits_per_pixel, &game->line_length, &game->endian);
	return (0);
}

void	set_colors(t_game *game, t_map *map)
{
	game->ceiling_color = (map->ceiling_rgb[0] << 16)
		| (map->ceiling_rgb[1] << 8) | map->ceiling_rgb[2];
	game->floor_color = (map->floor_rgb[0] << 16)
		| (map->floor_rgb[1] << 8) | map->floor_rgb[2];
}
