/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:04:43 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/20 14:44:32 by ysetiawa         ###   ########.fr       */
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
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

// void render_walls(t_game *game)
// {
// 	t_ray r;
// 	int x;
// 	int y;

// 	x = 0;
// 	while (x < game->win_w)
// 	{
// 		r.camera_x = 2 * x / (double)game->win_w - 1;
// 		r.ray_dir_x = game->p->dir_x + game->p->pln_x * r.camera_x;
// 		r.ray_dir_y = game->p->dir_y + game->p->pln_y * r.camera_x;

// 		r.map_x = (int)game->p->x;
// 		r.map_y = (int)game->p->y;

// 		r.dist_chge_x = fabs(1 / r.ray_dir_x);
// 		r.dist_chge_y = fabs(1 / r.ray_dir_y);

// 		r.hit = 0;

// 		if (r.ray_dir_x < 0)
// 		{
// 			r.step_x = -1;
// 			r.side_dist_x = (game->p->x - r.map_x) * r.dist_chge_x;
// 		}
// 		else
// 		{
// 			r.step_x = 1;
// 			r.side_dist_x = (r.map_x + 1.0 - game->p->x) * r.dist_chge_x;
// 		}
// 		if (r.ray_dir_y < 0)
// 		{
// 			r.step_y = -1;
// 			r.side_dist_y = (game->p->y - r.map_y) * r.dist_chge_y;
// 		}
// 		else
// 		{
// 			r.step_y = 1;
// 			r.side_dist_y = (r.map_y + 1.0 - game->p->y) * r.dist_chge_y;
// 		}

// 		while (!r.hit)
// 		{
// 			if (r.side_dist_x < r.side_dist_y)
// 			{
// 				r.side_dist_x += r.dist_chge_x;
// 				r.map_x += r.step_x;
// 				r.side = 0;
// 			}
// 			else
// 			{
// 				r.side_dist_y += r.dist_chge_y;
// 				r.map_y += r.step_y;
// 				r.side = 1;
// 			}
// 			if (r.map_x < 0 || r.map_x >= game->map->map_w ||
// 				r.map_y < 0 || r.map_y >= game->map->map_h)
// 				break; // Don't try to access invalid map tile
// 			if (game->map->map[r.map_y][r.map_x] == '1')
// 				r.hit = 1;
// 		}

// 		if (!r.hit)
// 		{
// 			y = 0;
// 			while (y < game->win_h / 2)
// 			{
// 				if (my_mlx_pixel_put(game, x, y++, game->ceiling_color))
// 					break;
// 			}
// 			while (y < game->win_h)
// 			{
// 				if (my_mlx_pixel_put(game, x, y++, game->floor_color))
// 					break;
// 			}
// 			x++;
// 			continue;
// 		}

// 		if (r.side == 0)
// 			r.wall_dist = (r.map_x - game->p->x + (1 - r
//.step_x) / 2) / r.ray_dir_x;
// 		else
// 			r.wall_dist = (r.map_y - game->p->y + (1 -
// r.step_y) / 2) / r.ray_dir_y;

// 		r.line_h = (int)(game->win_h / r.wall_dist);
// 		r.top_draw = game->win_h / 2 - r.line_h / 2;
// 		if (r.top_draw < 0)
// 			r.top_draw = 0;
// 		r.btm_draw = game->win_h / 2 + r.line_h / 2;
// 		if (r.btm_draw >= game->win_h)
// 			r.btm_draw = game->win_h - 1;

// 		void *texture;
// 		texture = NULL;
// 		if (r.side == 0)
// 		{
// 			if (r.step_x > 0)
// 				texture = game->tex_we;
// 			else
// 				texture = game->tex_ea;
// 		}
// 		else
// 		{
// 			if (r.step_y > 0)
// 				texture = game->tex_no;
// 			else
// 				texture = game->tex_so;
// 		}

// 		int tex_bpp, tex_line_size, tex_endian;
// 		char *tex = mlx_get_data_addr(texture, 
//&tex_bpp, &tex_line_size, &tex_endian);

// 		double wall_x;
// 		if (r.side == 0)
// 			wall_x = game->p->y + r.wall_dist * r.ray_dir_y;
// 		else
// 			wall_x = game->p->x + r.wall_dist * r.ray_dir_x;
// 		wall_x -= floor(wall_x);

// 		int tex_x = (int)(wall_x * TEX_W);
// 		if ((r.side == 0 && r.ray_dir_x > 0) || 
//(r.side == 1 && r.ray_dir_y < 0))
// 			tex_x = TEX_W - tex_x - 1;

// 		y = 0;
// 		while (y < r.top_draw)
// 			if (my_mlx_pixel_put(game, x, y++, game->ceiling_color))
// 				break;

// 		double step = (double)TEX_H / r.line_h;
// 		double tex_pos = (r.top_draw - game->win_h / 2 + r.line_h / 2) * step;

// 		y = r.top_draw;
// 		while (y <= r.btm_draw)
// 		{
// 			int tex_y = (int)tex_pos & (TEX_H - 1);
// 			tex_pos += step;
// 			unsigned int color = *(unsigned int*)(tex_
//data + (tex_y * tex_line_size + tex_x * (tex_bpp / 8)));
// 			if (r.side == 1)
// 				color = (color >> 1) & 0x7F7F7F; // darken y-side
// 			if (my_mlx_pixel_put(game, x, y++, color))
// 				break;
// 		}

// 		while (y < game->win_h)
// 			if (my_mlx_pixel_put(game, x, y++, game->floor_color))
// 				break;

// 		x++;
// 	}
// }
