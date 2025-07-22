/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location_updates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:41:15 by nsan              #+#    #+#             */
/*   Updated: 2025/05/22 20:22:42 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x + game->p->dir_x * 0.01;
	new_y = game->p->y + game->p->dir_y * 0.01;
	if (game->map->map[(int)game->p->y][(int)new_x] != '1' &&
		game->map->map[(int)game->p->y][(int)new_x] != 'D')
		game->p->x = new_x;
	if (game->map->map[(int)new_y][(int)game->p->x] != '1' &&
		game->map->map[(int)new_y][(int)game->p->x] != 'D')
		game->p->y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x - game->p->dir_x * 0.01;
	new_y = game->p->y - game->p->dir_y * 0.01;
	if (game->map->map[(int)game->p->y][(int)new_x] != '1' &&
		game->map->map[(int)game->p->y][(int)new_x] != 'D')
		game->p->x = new_x;
	if (game->map->map[(int)new_y][(int)game->p->x] != '1' &&
		game->map->map[(int)new_y][(int)game->p->x] != 'D')
		game->p->y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x - game->p->dir_y * 0.01;
	new_y = game->p->y + game->p->dir_x * 0.01;
	if (game->map->map[(int)game->p->y][(int)new_x] != '1' &&
		game->map->map[(int)game->p->y][(int)new_x] != 'D')
		game->p->x = new_x;
	if (game->map->map[(int)new_y][(int)game->p->x] != '1' &&
		game->map->map[(int)new_y][(int)game->p->x] != 'D')
		game->p->y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x + game->p->dir_y * 0.01;
	new_y = game->p->y - game->p->dir_x * 0.01;
	if (game->map->map[(int)game->p->y][(int)new_x] != '1' &&
		game->map->map[(int)game->p->y][(int)new_x] != 'D')
		game->p->x = new_x;
	if (game->map->map[(int)new_y][(int)game->p->x] != '1' &&
		game->map->map[(int)new_y][(int)game->p->x] != 'D')
		game->p->y = new_y;
}
