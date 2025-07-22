/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:39 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 16:22:52 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		putstr_fd("Error: Failed to initialize MLX\n", 2);
		return (1);
	}
	return (0);
}

void	init_ray(t_ray *r, t_game *game, int x)
{
	r->camera_x = 2 * x / (double)game->win_w - 1;
	r->ray_dir_x = game->p->dir_x + game->p->pln_x * r->camera_x;
	r->ray_dir_y = game->p->dir_y + game->p->pln_y * r->camera_x;
	r->map_x = (int)game->p->x;
	r->map_y = (int)game->p->y;
	r->dist_chge_x = fabs(1 / r->ray_dir_x);
	r->dist_chge_y = fabs(1 / r->ray_dir_y);
	r->hit = 0;
	r->hit_door = 0;
}

int	init_win(t_game *game, t_map *map, t_player *player)
{
	init_player(player, map);
	init_game(map, game, player);
	init_game1(game);
	if (init_mlx(game) || create_window(game) || create_image(game))
		return (1);
	set_colors(game, map);
	if (load_textures(game, map))
		return (1);
	return (0);
}
