/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:49 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/19 21:13:28 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_game(t_game *game)
{
	if (game->move_forward)
		move_forward(game);
	if (game->move_backward)
		move_backward(game);
	if (game->move_left)
		move_left(game);
	if (game->move_right)
		move_right(game);
	if (game->rotate_left)
		rotate_left(game);
	if (game->rotate_right)
		rotate_right(game);
	render_frame(game);
	return (0);
}

int	handle_down(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_W)
		game->move_forward = 1;
	else if (key == KEY_S)
		game->move_backward = 1;
	else if (key == KEY_A)
		game->move_left = 1;
	else if (key == KEY_D)
		game->move_right = 1;
	else if (key == KEY_LEFT)
		game->rotate_left = 1;
	else if (key == KEY_RIGHT)
		game->rotate_right = 1;
	return (0);
}

int	handle_up(int key, t_game *game)
{
	if (key == KEY_W)
		game->move_forward = 0;
	else if (key == KEY_S)
		game->move_backward = 0;
	else if (key == KEY_A)
		game->move_left = 0;
	else if (key == KEY_D)
		game->move_right = 0;
	else if (key == KEY_LEFT)
		game->rotate_left = 0;
	else if (key == KEY_RIGHT)
		game->rotate_right = 0;
	return (0);
}
