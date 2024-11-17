/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:29:22 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/10/25 23:33:58 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

void	init_game(t_map *map_s, t_game *game)
{
	game->map = map_s;
	game->win_w = map_s->map_w * 64;
	game->win_h = map_s->map_h * 64;
	game->player = NULL;
	game->wall = NULL;
	game->collectible = NULL;
	game->floor = NULL;
	game->exit = NULL;
	game->moves = 1;
	game->new_y = 0;
	game->new_x = 0;
	game->prev_x = 0;
	game->prev_y = 0;
}

int	init_win(t_game *game, t_map *map_s)
{
	init_game(map_s, game);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		ft_printf("Error: Failed to initialize MLX\n");
		return (1);
	}
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "so_long");
	if (game->win == NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		ft_printf("Error: Failed to create window\n");
		return (1);
	}
	return (0);
}

void	init_map(t_map *map_s, t_temp *temp)
{
	map_s->map = NULL;
	map_s->map_cp = NULL;
	map_s->map_fd = -1;
	map_s->map_w = 0;
	map_s->map_h = 0;
	map_s->collect = 0;
	map_s->player = 0;
	map_s->exit = 0;
	map_s->player_x = -1;
	map_s->player_y = -1;
	temp->c = 0;
	temp->e = 0;
}
