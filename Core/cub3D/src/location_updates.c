/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location_updates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:58 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/21 16:20:27 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x + game->p->dir_x * 0.01;
	new_y = game->p->y + game->p->dir_y * 0.01;
	game->p->x = new_x;
	game->p->y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x - game->p->dir_x * 0.01;
	new_y = game->p->y - game->p->dir_y * 0.01;
	game->p->x = new_x;
	game->p->y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x - game->p->dir_y * 0.01;
	new_y = game->p->y + game->p->dir_x * 0.01;
	game->p->x = new_x;
	game->p->y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p->x + game->p->dir_y * 0.01;
	new_y = game->p->y - game->p->dir_x * 0.01;
	game->p->x = new_x;
	game->p->y = new_y;
}
