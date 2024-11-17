/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:24:36 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/25 23:52:15 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

void	cleanup_game(t_game *game)
{
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->player)
			mlx_destroy_image(game->mlx, game->player);
		if (game->wall)
			mlx_destroy_image(game->mlx, game->wall);
		if (game->collectible)
			mlx_destroy_image(game->mlx, game->collectible);
		if (game->floor)
			mlx_destroy_image(game->mlx, game->floor);
		if (game->exit)
			mlx_destroy_image(game->mlx, game->exit);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	load_single(t_game *game, void **img_ptr, char *filename)
{
	int	width;
	int	height;

	*img_ptr = mlx_xpm_file_to_image(game->mlx, filename, &width, &height);
	if (!*img_ptr)
		ft_printf("Error: Failed to load %s\n", filename);
}

void	load_images(t_game *game)
{
	load_single(game, &game->player, "textures/player.xpm");
	load_single(game, &game->wall, "textures/wall.xpm");
	load_single(game, &game->collectible, "textures/collectibles.xpm");
	load_single(game, &game->floor, "textures/floor.xpm");
	load_single(game, &game->exit, "textures/exit.xpm");
	if (!game->wall || !game->floor || !game->player || \
	!game->collectible || !game->exit)
	{
		if (game->player)
			mlx_destroy_image(game->mlx, game->player);
		if (game->wall)
			mlx_destroy_image(game->mlx, game->wall);
		if (game->exit)
			mlx_destroy_image(game->mlx, game->exit);
		if (game->floor)
			mlx_destroy_image(game->mlx, game->floor);
		if (game->collectible)
			mlx_destroy_image(game->mlx, game->collectible);
		ft_printf("Error: Failed to load images\n");
		exit(1);
	}
}

void	put_image(t_game *game, t_map *map_s, int x, int y)
{
	if (map_s->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->wall, x * 64, y * 64);
	else if (map_s->map[y][x] == '0')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->floor, x * 64, y * 64);
	else if (map_s->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->player, x * 64, y * 64);
	else if (map_s->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->collectible, x * 64, y * 64);
	else if (map_s->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->exit, x * 64, y * 64);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->map_h)
	{
		x = 0;
		while (x < game->map->map_w)
		{
			put_image(game, game->map, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
