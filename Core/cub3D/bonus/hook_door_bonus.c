/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:44:44 by nsan              #+#    #+#             */
/*   Updated: 2025/05/25 16:35:31 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_adjacent_to_player(int px, int py, int dx, int dy)
{
	return ((px == dx && (py == dy - 1 || py == dy + 1))
		|| (py == dy && (px == dx - 1 || px == dx + 1)));
}

void	toggle_door_state(t_game *game, int i, int dx, int dy)
{
	if (game->map->doors[i].door_state == 0)
	{
		game->map->doors[i].door_state = 1;
		game->map->map[dy][dx] = '0';
		game->map->doors[i].redraw = 1;
	}
	else
	{
		game->map->doors[i].door_state = 0;
		game->map->map[dy][dx] = 'D';
		game->map->doors[i].redraw = 0;
	}
}

void	open_door(t_game *game)
{
	int	i;
	int	px;
	int	py;
	int	dx;
	int	dy;

	px = (int)game->p->x;
	py = (int)game->p->y;
	i = 0;
	while (i < game->map->door_count)
	{
		dx = game->map->doors[i].door_x;
		dy = game->map->doors[i].door_y;
		if (is_adjacent_to_player(px, py, dx, dy) && game->player_next_to_door)
		{
			toggle_door_state(game, i, dx, dy);
			break ;
		}
		i++;
	}
	game->press_space = 0;
}
