/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:04:43 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/22 20:24:58 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_ray(t_ray *r, t_game *game)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->p->x - r->map_x) * r->dist_chge_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - game->p->x) * r->dist_chge_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->p->y - r->map_y) * r->dist_chge_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - game->p->y) * r->dist_chge_y;
	}
}

void	perform_dda(t_ray *r, t_game *game)
{
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->dist_chge_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->dist_chge_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_x >= game->map->map_w
			|| r->map_y < 0 || r->map_y >= game->map->map_h)
			break ;
		if (game->map->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
		else if (game->map->map[r->map_y][r->map_x] == 'D')
		{
			r->hit = 1;
			r->hit_door = 1;
		}
	}
}

void	calculate_wall_x(t_ray *r, t_game *game, double *wall_x, int *tex_x)
{
	if (r->side == 0)
		*wall_x = game->p->y + r->wall_dist * r->ray_dir_y;
	else
		*wall_x = game->p->x + r->wall_dist * r->ray_dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * TEX_W);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		*tex_x = TEX_W - *tex_x - 1;
}

void	render_walls(t_game *game)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < game->win_w)
	{
		init_ray(&r, game, x);
		step_ray(&r, game);
		perform_dda(&r, game);
		draw_walls(game, &r, x);
		x++;
	}
}

void	render_frame(t_game *game)
{
	clear_image(game);
	render_walls(game);
	render_sprites(game, game->z_buffer);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
