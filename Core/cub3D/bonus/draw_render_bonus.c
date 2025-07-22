/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:36 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/22 18:47:54 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *game, int x, int top_draw)
{
	int	y;

	y = 0;
	while (y < top_draw)
	{
		if (my_mlx_pixel_put(game, x, y++, game->ceiling_color))
			break ;
	}
}

void	draw_floor(t_game *game, int x, int bottom_draw)
{
	int	y;

	y = bottom_draw;
	while (y < game->win_h)
	{
		if (my_mlx_pixel_put(game, x, y++, game->floor_color))
			break ;
	}
}

void	draw_texture(t_game *game, t_ray *r, void *tex, int x)
{
	t_texture		text;
	int				tex_y;
	unsigned int	color;

	text.tex = mlx_get_data_addr(tex, &text.tex_bpp,
			&text.tex_line_size, &text.tex_endian);
	calculate_wall_x(r, game, &text.wall_x, &text.tex_x);
	draw_ceiling(game, x, r->top_draw);
	text.step = (double)TEX_H / r->line_h;
	text.tex_pos = (r->top_draw - game->win_h / 2
			+ r->line_h / 2) * text.step;
	text.y = r->top_draw;
	while (text.y <= r->btm_draw)
	{
		tex_y = (int)text.tex_pos & (TEX_H - 1);
		text.tex_pos += text.step;
		color = *(unsigned int *)(text.tex + (tex_y * text.tex_line_size
					+ text.tex_x * (text.tex_bpp / 8)));
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		if (my_mlx_pixel_put(game, x, text.y++, color))
			break ;
	}
	draw_floor(game, x, text.y);
}

void	draw_walls(t_game *game, t_ray *r, int x)
{
	void	*texture;

	if (handle_no_hit(game, r, x))
		return ;
	calculate_wall_data(game, r, x);
	texture = select_texture(game, r);
	draw_texture(game, r, texture, x);
}
