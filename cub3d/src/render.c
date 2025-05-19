/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:04:43 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/19 16:53:26 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_walls(t_game *game)
{
	t_ray r;
	int x;
	int y;

	x = 0;
	while (x < game->win_w)
	{
		r.camera_x = 2 * x / (double)game->win_w - 1;
		r.ray_dir_x = game->p->dir_x + game->p->plane_x * r.camera_x;
		r.ray_dir_y = game->p->dir_y + game->p->plane_y * r.camera_x;

		r.map_x = (int)game->p->x;
		r.map_y = (int)game->p->y;

		r.dist_chge_x = fabs(1 / r.ray_dir_x);
		r.dist_chge_y = fabs(1 / r.ray_dir_y);

		r.hit = 0;
		r.hit_door = 0;

		r.step_x = (r.ray_dir_x < 0) ? -1 : 1;
		r.side_dist_x = (r.ray_dir_x < 0)
			? (game->p->x - r.map_x) * r.dist_chge_x
			: (r.map_x + 1.0 - game->p->x) * r.dist_chge_x;

		r.step_y = (r.ray_dir_y < 0) ? -1 : 1;
		r.side_dist_y = (r.ray_dir_y < 0)
			? (game->p->y - r.map_y) * r.dist_chge_y
			: (r.map_y + 1.0 - game->p->y) * r.dist_chge_y;

		while (!r.hit)
		{
			if (r.side_dist_x < r.side_dist_y)
			{
				r.side_dist_x += r.dist_chge_x;
				r.map_x += r.step_x;
				r.side = 0;
			}
			else
			{
				r.side_dist_y += r.dist_chge_y;
				r.map_y += r.step_y;
				r.side = 1;
			}

			if (r.map_x < 0 || r.map_x >= game->map->map_w ||
				r.map_y < 0 || r.map_y >= game->map->map_h)
			{
				break; // Don't try to access invalid map tile
			}
			
			char tile = game->map->map[r.map_y][r.map_x];
			if (tile == '1')
				r.hit = 1;
			else if (tile == 'D')
			{
				r.hit = 1;
				r.hit_door = 1;
			}
		}

		if (!r.hit)
		{
			y = 0;
			while (y < game->win_h / 2)
				my_mlx_pixel_put(game, x, y++, game->ceiling_color);
			while (y < game->win_h)
				my_mlx_pixel_put(game, x, y++, game->floor_color);
			x++;
			continue;
		}

		r.wall_dist = (r.side == 0)
			? (r.map_x - game->p->x + (1 - r.step_x) / 2) / r.ray_dir_x
			: (r.map_y - game->p->y + (1 - r.step_y) / 2) / r.ray_dir_y;

		r.line_h = (int)(game->win_h / r.wall_dist);
		r.top_draw = game->win_h / 2 - r.line_h / 2;
		if (r.top_draw < 0) r.top_draw = 0;
		r.btm_draw = game->win_h / 2 + r.line_h / 2;
		if (r.btm_draw >= game->win_h) r.btm_draw = game->win_h - 1;

		int d;

		d= 0;
		void *texture = NULL;
		if (r.hit_door)
		{
			// Match with correct door and check if it's open
			texture = game->tex_door;
			while (d < game->map->door_count)
			{
				if (game->map->doors[d].door_x == r.map_x &&
					game->map->doors[d].door_y == r.map_y &&
					game->map->doors[d].door_state == 1)
				{
					texture = game->tex_opening;
					break;
				}
				d++;
			}
		}
		else if (r.side == 0)
			texture = (r.step_x > 0) ? game->tex_we : game->tex_ea;
		else
			texture = (r.step_y > 0) ? game->tex_no : game->tex_so;

		int tex_bpp, tex_line_size, tex_endian;
		char *tex_data = mlx_get_data_addr(texture, &tex_bpp, &tex_line_size, &tex_endian);

		double wall_x = (r.side == 0)
			? game->p->y + r.wall_dist * r.ray_dir_y
			: game->p->x + r.wall_dist * r.ray_dir_x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * TEX_W);
		if ((r.side == 0 && r.ray_dir_x > 0) || (r.side == 1 && r.ray_dir_y < 0))
			tex_x = TEX_W - tex_x - 1;

		y = 0;
		while (y < r.top_draw)
			if (my_mlx_pixel_put(game, x, y++, game->ceiling_color))
				break;

		double step = (double)TEX_H / r.line_h;
		double tex_pos = (r.top_draw - game->win_h / 2 + r.line_h / 2) * step;

		y = r.top_draw;
		while (y <= r.btm_draw)
		{
			int tex_y = (int)tex_pos & (TEX_H - 1);
			tex_pos += step;
			unsigned int color = *(unsigned int*)(tex_data + (tex_y * tex_line_size + tex_x * (tex_bpp / 8)));
			if (r.side == 1)
				color = (color >> 1) & 0x7F7F7F; // darken y-side
			if (my_mlx_pixel_put(game, x, y++, color))
				break;
		}

		while (y < game->win_h)
			if (my_mlx_pixel_put(game, x, y++, game->floor_color))
				break;

		x++;
	}
}

void render_minimap(t_game *game)
{
	int x;
	int y;
	int i;
	int j;
	int color;

	y = 0;
	while (y < game->map->map_h)
	{
		x = 0;
		while (x < game->map->map_w)
		{
			if (game->map->map[y][x] == '1')
				color = 0x888888;
			else
				color = 0x000000;
			j = 0;
			while (j < MINIMAP_SCALE)
			{
				i = 0;
				while (i < MINIMAP_SCALE)
				{
					int px = x * MINIMAP_SCALE + i + MINIMAP_OFFSET_X;
					int py = y * MINIMAP_SCALE + j + MINIMAP_OFFSET_Y;
					my_mlx_pixel_put(game, px, py, color);
					i++;
				}
				j++;
			}
			x++;
		}
		y++;
	}

	// Player on the minimap
	int player_px;
	int player_py;
	
	player_px = game->p->x * MINIMAP_SCALE + MINIMAP_OFFSET_X;
	player_py = game->p->y * MINIMAP_SCALE + MINIMAP_OFFSET_Y;
	j = -1;
	while (j <= 1)
	{
		i = -1;
		while (i <= 1)
		{
			my_mlx_pixel_put(game, player_px + i, player_py + j, 0xFF0000);
			i++;
		}
		j++;
	}

	// Direction line
	int line_len;
	int dir_x;
	int dir_y;
	int d;
	int px;
	int py;

	line_len = 5;
	dir_x = game->p->dir_x * line_len;
	dir_y = game->p->dir_y * line_len;
	d = 0;
	while (d < line_len)
	{
		px = player_px + dir_x * d;
		py = player_py + dir_y * d;
		my_mlx_pixel_put(game, px, py, 0x00FFFF);
		d++;
	}
}

void render_frame(t_game *game)
{
	// 1. Clear previous frame
	clear_image(game);

	// 2. Draw 3D scene using raycasting
	render_walls(game);
	// 3. Draw minimap
	render_minimap(game);

	// 4. Put the image to the window
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
