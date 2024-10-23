/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:35:39 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/23 18:28:40 by ysetiawa         ###   ########.fr       */
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

// enum
// {
//     ON_KEYDOWN = 2,
//     ON_KEYUP = 3,
//     ON_MOUSEDOWN = 4,
//     ON_MOUSEUP = 5,
//     ON_MOUSEMOVE = 6,
//     ON_EXPOSE = 12,
//     ON_DESTROY = 17
// };

typedef struct s_struct
{
    char    **map;
    char    **map_cp;
    int     map_fd;
    int     map_w;
    int     map_h;
    int     player_x;
    int     player_y;
    int     player;
    int     exit;
    int     collect;
}	t_struct;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    int     win_w;
    int     win_h;
    void	*player;
	void	*wall;
	void	*exit;
	void	*floor;
	void	*collectible;
    t_struct *m_struct;
}   t_game;

typedef struct s_temp
{
    int     e;
    int     c;
}	t_temp;

int	ft_strlen(const char *s);
int	ft_strcmp(char *s1, char *s2);
int check_filename(char *filename);
int    read_map(t_struct *m_struct, char **argv);
int	wordlen(const char *s, char c);
char	*writeword(char const *s, int len);
char	**free_array(char **ptr, int i);
char	**split_words(const char *s, char c, int word_count);
char	**ft_split(char const *s, char c);
void    init_map(t_struct *m_structs, t_temp *temp);
void	map_dimension(t_struct *m_structs);
int rect_check(t_struct *m_struct);
int wall_check(t_struct *m_struct);
void count_elems(t_struct *m_struct);
int valid_elem(t_struct *m_struct);
void check_elem(t_struct *m_struct);
void	floodfill(t_struct *m_struct, int y, int x, t_temp *temp);
void	startfill(t_struct *m_struct);
int map_valid(t_temp *temp);
void	free_2d(char **memory);
void	clean_struct(t_struct *m_struct);
void	ft_error(char *s, t_struct *m_struct);
void map_check(char **argv, t_struct *m_structs, t_temp *temp);

void    render_map(t_game *game, t_struct *m_struct);
void	load_images(t_game *game);
void	load_single(t_game *game, void **img_ptr, char *filename);
void handle_events(t_game *game);
void cleanup_game(t_game *game);
int close_window(t_game *game);
int    init_game(t_struct *m_structs, t_game *game);


#endif

// void free_all(t_struct *m_structs);