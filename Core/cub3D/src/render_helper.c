/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:55:24 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/20 14:45:12 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return (1);
	dst = game->img_addr + (y * game->line_length
			+ x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

void	clear_image(t_game *game)
{
	int	*dst;
	int	i;

	dst = (int *)game->img_addr;
	i = 0;
	while (i < (game->win_w * game->win_h))
	{
		dst[i] = 0x000000;
		i++;
	}
}

int	handle_no_hit(t_game *game, t_ray *r, int x)
{
	int	y;

	if (r->hit)
		return (0);
	y = 0;
	while (y < game->win_h / 2)
	{
		if (my_mlx_pixel_put(game, x, y++, game->ceiling_color))
			break ;
	}
	while (y < game->win_h)
	{
		if (my_mlx_pixel_put(game, x, y++, game->floor_color))
			break ;
	}
	return (1);
}

void	calculate_wall_data(t_game *game, t_ray *r)
{
	if (r->side == 0)
		r->wall_dist = (r->map_x - game->p->x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->wall_dist = (r->map_y - game->p->y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	r->line_h = (int)(game->win_h / r->wall_dist);
	r->top_draw = game->win_h / 2 - r->line_h / 2;
	if (r->top_draw < 0)
		r->top_draw = 0;
	r->btm_draw = game->win_h / 2 + r->line_h / 2;
	if (r->btm_draw >= game->win_h)
		r->btm_draw = game->win_h - 1;
}

void	*select_texture(t_game *game, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->step_x > 0)
			return (game->tex_we);
		else
			return (game->tex_ea);
	}
	else
	{
		if (r->step_y > 0)
			return (game->tex_no);
		else
			return (game->tex_so);
	}
}
