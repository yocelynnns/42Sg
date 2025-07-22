/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_updates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:10:20 by nsan              #+#    #+#             */
/*   Updated: 2025/05/22 20:22:19 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_pln_x;

	old_dir_x = game->p->dir_x;
	old_pln_x = game->p->pln_x;
	game->p->dir_x = game->p->dir_x * cos(0.01) - game->p->dir_y * sin(0.01);
	game->p->dir_y = old_dir_x * sin(0.01) + game->p->dir_y * cos(0.01);
	game->p->pln_x = game->p->pln_x * cos(0.01) - game->p->pln_y * sin(0.01);
	game->p->pln_y = old_pln_x * sin(0.01) + game->p->pln_y * cos(0.01);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_pln_x;

	old_dir_x = game->p->dir_x;
	old_pln_x = game->p->pln_x;
	game->p->dir_x = game->p->dir_x * cos(-0.01) - game->p->dir_y * sin(-0.01);
	game->p->dir_y = old_dir_x * sin(-0.01) + game->p->dir_y * cos(-0.01);
	game->p->pln_x = game->p->pln_x * cos(-0.01) - game->p->pln_y * sin(-0.01);
	game->p->pln_y = old_pln_x * sin(-0.01) + game->p->pln_y * cos(-0.01);
}

void	set_dir2(t_game *game)
{
	if (game->map->player_dir == 'E')
	{
		game->p->dir_x = 1;
		game->p->dir_y = 0;
		game->p->pln_x = 0;
		game->p->pln_y = 0.66;
	}
	else if (game->map->player_dir == 'W')
	{
		game->p->dir_x = -1;
		game->p->dir_y = 0;
		game->p->pln_x = 0;
		game->p->pln_y = -0.66;
	}
}

void	set_dir(t_game *game)
{
	if (game->map->player_dir == 'N')
	{
		game->p->dir_x = 0;
		game->p->dir_y = -1;
		game->p->pln_x = 0.66;
		game->p->pln_y = 0;
	}
	else if (game->map->player_dir == 'S')
	{
		game->p->dir_x = 0;
		game->p->dir_y = 1;
		game->p->pln_x = -0.66;
		game->p->pln_y = 0;
	}
	else if (game->map->player_dir == 'E' || game->map->player_dir == 'W')
		set_dir2(game);
}
