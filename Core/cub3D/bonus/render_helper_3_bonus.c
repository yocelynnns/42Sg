/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:34:55 by nsan              #+#    #+#             */
/*   Updated: 2025/05/25 16:22:52 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_door_animation(t_game *game, int door_index)
{
	int	tex_w;
	int	tex_h;
	int	dx;
	int	dy;

	game->tex_opening = mlx_xpm_file_to_image(game->mlx,
			game->map->door_path, &tex_w, &tex_h);
	if (!game->tex_opening)
	{
		putstr_fd("Error: Failed to load door opening texture\n", 2);
		return ;
	}
	dx = game->map->doors[door_index].door_x;
	dy = game->map->doors[door_index].door_y;
	mlx_put_image_to_window(game->mlx, game->win,
		game->tex_opening, dx * 64, dy * 64);
}

//render sprites helper
void	render_single_sprite(t_game *game, double *z_buffer, t_sprite *s)
{
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_size;
	t_draw_data	draw;

	calculate_sprite_transform(game, s, &transform_x, &transform_y);
	if (transform_y <= 0.1)
		return ;
	sprite_screen_x = (int)((game->win_w / 2)
			* (1 + transform_x / transform_y));
	sprite_size = abs((int)(game->win_h / transform_y * 0.25));
	draw.sprite_screen_x = sprite_screen_x;
	draw.size = sprite_size;
	draw.transform_y = transform_y;
	calculate_draw_bounds(game, &draw);
	draw_sprite_stripe(game, z_buffer, s, &draw);
}

void	render_sprites(t_game *game, double *z_buffer)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		render_single_sprite(game, z_buffer, &game->sprites[i]);
		i++;
	}
}
