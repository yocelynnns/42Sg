/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:14:15 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/27 15:50:18 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <../minilibx-linux/mlx.h>
# include <math.h>
# include <stdbool.h>

# define BUFFER_SIZE 700

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_A 97
# define KEY_D 100
# define KEY_S 115
# define KEY_W 119
# define KEY_ESC 65307
# define KEY_SPACE 32

# define TEX_W 64
# define TEX_H 64

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_map
{
	char	**lines;
	char	**map;
	char	**map_cp;
	int		map_w;
	int		map_h;
	int		map_fd;
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	double	player_x;
	double	player_y;
	char	player_dir;
	int		p_count;
	bool	has_no;
	bool	has_so;
	bool	has_ea;
	bool	has_we;
	bool	has_floor;
	bool	has_ceiling;
}	t_map;

// t_player
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	pln_x;
	double	pln_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	dist_chge_x;
	double	dist_chge_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_dist;
	int		line_h;
	int		top_draw;
	int		btm_draw;
	int		color;
}	t_ray;

typedef struct s_texture
{
	int		tex_bpp;
	int		tex_line_size;
	int		tex_endian;
	char	*tex;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	int			move_forward;
	int			move_backward;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
	char		*img;
	char		*img_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			ceiling_color;
	int			floor_color;
	void		*tex_no;
	void		*tex_so;
	void		*tex_we;
	void		*tex_ea;
	t_map		*map;
	t_player	*p;
}	t_game;

// direction_updates.c
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
void	set_dir2(t_game *game);
void	set_dir(t_game *game);

// draw_render.c
void	draw_ceiling(t_game *game, int x, int top_draw);
void	draw_floor(t_game *game, int x, int bottom_draw);
void	draw_texture(t_game *game, t_ray *r, void *texture, int x);
void	draw_walls(t_game *game, t_ray *r, int x);

// free_n_err.c
void	free_arr(char **arr);
void	clean_struct(t_map *map_s);
void	ft_error(char *s, t_map *map_s);
int		close_window(t_game *game);
void	cleanup_game(t_game *game);

// ft_hooks.c
int		update_game(t_game *game);
int		handle_down(int key, t_game *game);
int		handle_up(int key, t_game *game);

// helper.c
int		check_filename(char *filename);
int		ends_with_xpm(char *path);

// inits.c
void	init_map(t_map *map);
void	init_game(t_map *map, t_game *game, t_player *player);
void	init_player(t_player *player, t_map *map);

// inits2.c
int		init_win(t_game *game, t_map *map, t_player *player);
void	init_ray(t_ray *r, t_game *game, int x);
int		init_mlx(t_game *game);

// location_updates.c
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);

// map_check.c
int		valid_elements(t_map *map);
void	map_dimension(t_map *map);
void	count_and_check_player(t_map *map);

// map_check2.c
void	print_map_cp(char **map_cp);
void	floodfill(t_map *map, int y, int x);
void	map_check(char **argv, t_map *map);

// map_helper.c
char	*get_full_buffer(int fd);
char	**duplicate_map(char **map);
void	add_line_to_map(t_map *map, char *line);
int		open_map_file(t_map *map, char **argv);

// map_helper2.c
char	**get_lines_from_buffer(t_map *map);
int		process_lines(t_map *map, char **lines);
int		read_map(t_map *map, char **argv);
int		is_map_line(char *line);

// parse_textures.c
int		parse_color(int *color_array, char *str);
int		set_texture_path(char **path, char *line);
int		parse_texture_color(t_map *map, char *line);

// parse_textures2.c
int		create_window(t_game *game);
int		create_image(t_game *game);
void	set_colors(t_game *game, t_map *map);
int		load_textures(t_game *game, t_map *map);

// parse_textures3.c
int		handle_no(t_map *map, char *line);
int		handle_so(t_map *map, char *line);
int		handle_ea(t_map *map, char *line);
int		handle_we(t_map *map, char *line);

// render_helper.c
int		my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	clear_image(t_game *game);
int		handle_no_hit(t_game *game, t_ray *r, int x);
void	calculate_wall_data(t_game *game, t_ray *r);
void	*select_texture(t_game *game, t_ray *r);

// render.c
void	step_ray(t_ray *r, t_game *game);
void	perform_dda(t_ray *r, t_game *game);
void	calculate_wall_x(t_ray *r, t_game *game, double *wall_x, int *tex_x);
void	render_walls(t_game *game);
void	render_frame(t_game *game);

#endif