/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:45:13 by nsan              #+#    #+#             */
/*   Updated: 2025/05/22 20:23:31 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	animation_loop(t_game *game)
{
	int	i;

	i = 0;
	game->anim_counter++;
	if (game->anim_counter >= 10)
	{
		while (i < game->sprite_count)
		{
			game->sprites[i].current_frame
				= (game->sprites[i].current_frame + 1) % SPRITE_FRAMES;
			i++;
		}
		game->anim_counter = 0;
	}
}

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
	if (game->press_space)
		open_door(game);
	check_player_to_door(game);
	animation_loop(game);
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
	else if (key == KEY_SPACE)
		game->press_space = 1;
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
