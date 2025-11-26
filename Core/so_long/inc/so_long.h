/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:35:39 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/26 16:17:23 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <mlx.h>

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
	char	**map;
	char	**map_cp;
	int		map_fd;
	int		map_w;
	int		map_h;
	int		player_x;
	int		player_y;
	int		player;
	int		exit;
	int		collect;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	void		*player;
	void		*wall;
	void		*exit;
	void		*floor;
	void		*collectible;
	int			moves;
	int			new_y;
	int			new_x;
	int			prev_y;
	int			prev_x;
	t_map		*map;
}	t_game;

typedef struct s_temp
{
	int	e;
	int	c;
}	t_temp;

int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		check_filename(char *filename);
int		read_map(t_map *map_s, char **argv);
int		wordlen(const char *s, char c);
char	*writeword(char const *s, int len);
char	**free_array(char **ptr, int i);
char	**split_words(const char *s, char c, int word_count);
char	**ft_split(char const *s, char c);
void	init_map(t_map *map_s, t_temp *temp);
void	map_dimension(t_map *map_s);
int		rect_check(t_map *map_s);
int		wall_check(t_map *map_s);
void	count_elems(t_map *map_s);
int		valid_elem(t_map *map_s);
void	check_elem(t_map *map_s);
void	floodfill(t_map *map_s, int y, int x, t_temp *temp);
void	startfill(t_map *map_s);
int		map_valid(t_temp *temp);
void	free_arr(char **arr);
void	clean_struct(t_map *map_s);
void	ft_error(char *s, t_map *map_s);
void	map_check(char **argv, t_map *map_s);

int		render_map(t_game *game);
void	load_images(t_game *game);
void	load_single(t_game *game, void **img_ptr, char *filename);
void	cleanup_game(t_game *game);
int		close_window(t_game *game);
void	init_game(t_map *map_s, t_game *game);
int		init_win(t_game *game, t_map *map_s);
void	put_image(t_game *game, t_map *map_s, int x, int y);

void	movement(t_game *game, int new_y, int new_x, int key);
int		key_movement(int key, t_game *game);
int		valid_movement(t_map *map, int new_y, int new_x);
void	update_position(t_game *game, int new_y, int new_x);
void	update_previous_position(t_game *game);

#endif
