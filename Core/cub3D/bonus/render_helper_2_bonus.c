/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:29:07 by nsan              #+#    #+#             */
/*   Updated: 2025/05/22 20:24:28 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_sprite_transform(t_game *game, t_sprite *s,
	double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = s->x - game->p->x;
	sprite_y = s->y - game->p->y;
	inv_det = 1.0 / (game->p->pln_x * game->p->dir_y
			- game->p->dir_x * game->p->pln_y);
	*transform_x = inv_det * (game->p->dir_y * sprite_x - game->p->dir_x
			* sprite_y);
	*transform_y = inv_det * (-game->p->pln_y * sprite_x + game->p->pln_x
			* sprite_y);
}

void	calculate_draw_bounds(t_game *game, t_draw_data *draw)
{
	draw->start_y = -draw->size / 2 + game->win_h / 2;
	draw->end_y = draw->size / 2 + game->win_h / 2;
	draw->start_x = -draw->size / 2 + draw->sprite_screen_x;
	draw->end_x = draw->size / 2 + draw->sprite_screen_x;
}

static int	get_tex_y(int y, int win_h, int size)
{
	int	d;

	d = (y - win_h / 2 + size / 2) * TEX_H;
	return (d / size);
}

static void	draw_sprite_column(t_game *game, t_draw_data *draw,
	char *tex_data)
{
	int	y;
	int	tex_y;
	int	color;
	int	tex_x;

	tex_x = (int)((draw->stripe - (draw->sprite_screen_x
					- draw->size / 2)) * TEX_W / draw->size);
	y = draw->start_y;
	while (y < draw->end_y)
	{
		if (y >= 0 && y < game->win_h)
		{
			tex_y = get_tex_y(y, game->win_h, draw->size);
			color = *(unsigned int *)(tex_data
					+ (tex_y * draw->line_size + tex_x
						* (draw->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(game, draw->stripe, y, color);
		}
		y++;
	}
}

void	draw_sprite_stripe(t_game *game, double *z_buffer,
	t_sprite *s, t_draw_data *draw)
{
	int		endian;

	draw->tex = game->tex_coin[s->current_frame];
	draw->tex_data = mlx_get_data_addr(draw->tex,
			&draw->bpp, &draw->line_size, &endian);
	draw->stripe = draw->start_x;
	while (draw->stripe < draw->end_x)
	{
		if (draw->stripe >= 0 && draw->stripe < game->win_w
			&& draw->transform_y < z_buffer[draw->stripe])
			draw_sprite_column(game, draw, draw->tex_data);
		draw->stripe++;
	}
}
