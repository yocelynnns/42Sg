/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:18:02 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/26 17:10:03 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

int	valid_movement(t_map *map, int new_y, int new_x)
{
	if (new_x < 0 || new_x >= map->map_w - 1 || new_y < 0
		|| new_y >= map->map_h - 1)
		return (0);
	if (map->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

int	key_movement(int key, t_game *game)
{
	game->new_y = game->map->player_y;
	game->new_x = game->map->player_x;
	if (key == KEY_UP || key == KEY_W)
		game->new_y--;
	else if (key == KEY_DOWN || key == KEY_S)
		game->new_y++;
	else if (key == KEY_LEFT || key == KEY_A)
		game->new_x--;
	else if (key == KEY_RIGHT || key == KEY_D)
		game->new_x++;
	else if (key == KEY_ESC)
		close_window(game);
	movement(game, game->new_y, game->new_x, key);
	return (0);
}

void	movement(t_game *game, int new_y, int new_x, int key)
{
	if (!valid_movement(game->map, new_y, new_x))
		return ;
	if (game->map->map[new_y][new_x] == 'C')
		game->map->collect--;
	if (game->map->map[new_y][new_x] == 'E' && game->map->collect == 0)
	{
		ft_printf("Moves: %d\n", game->moves++);
		ft_printf("\n");
		ft_printf("\033[1;32mSuccess! You win\033[0m\n");
		close_window(game);
	}
	game->prev_x = game->map->player_x;
	game->prev_y = game->map->player_y;
	update_previous_position(game);
	update_position(game, new_y, new_x);
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D
		|| key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT
		|| key == KEY_RIGHT)
		ft_printf("Moves: %d\n", game->moves++);
}

void	update_position(t_game *game, int new_y, int new_x)
{
	game->map->player_x = new_x;
	game->map->player_y = new_y;
	if (game->map->map[new_y][new_x] != 'E')
		game->map->map[new_y][new_x] = 'P';
	mlx_put_image_to_window(game->mlx, game->win, \
	game->player, new_x * 64, new_y * 64);
}

void	update_previous_position(t_game *game)
{
	if (game->map->map[game->prev_y][game->prev_x] == 'P' \
	&& game->map->map[game->prev_y][game->prev_x] != 'E')
	{
		game->map->map[game->prev_y][game->prev_x] = '0';
		mlx_put_image_to_window(game->mlx, game->win, \
		game->floor, game->prev_x * 64, game->prev_y * 64);
	}
	else
	{
		game->map->map[game->prev_y][game->prev_x] = 'E';
		mlx_put_image_to_window(game->mlx, game->win, \
		game->exit, game->prev_x * 64, game->prev_y * 64);
	}
}

// ft_printf("----------------------\n");
// ft_printf("new: %d %d\n", game->new_x, game->new_y);
// ft_printf("prev: %d %d\n", game->prev_x, game->prev_y);

// mlx_put_image_to_window(game->mlx, 
// game->win, game->floor, game->prev_x * 64, game->prev_y * 64);

// else if (game->map->map[game->prev_y][game->prev_x] != 'E')
// {
// 	game->map->map[game->prev_y][game->prev_x] = 'E';
// 	// mlx_put_image_to_window(game->mlx, game->win, 
// 	// game->exit, game->prev_x * 64, game->prev_y * 64);
// }

// if (game->map->map[game->prev_y][game->prev_x] == '0')
// {
// 	// game->map->map[game->prev_y][game->prev_x] = '0';
// 	mlx_put_image_to_window(game->mlx, game->win, 
// 	game->floor, game->prev_x * 64, game->prev_y * 64);
// }
// if (game->map->map[game->prev_y][game->prev_x] == 'E')
// {
// 	mlx_put_image_to_window(game->mlx, game->win, 
// 	game->exit, game->prev_x * 64, game->prev_y * 64);
// 	// game->map->map[game->prev_y][game->prev_x] = 'E';
// }