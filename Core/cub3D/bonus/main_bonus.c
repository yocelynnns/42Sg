/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:12:31 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 16:22:52 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_sprites(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->sprite_count = 0;
	while (y < game->map->map_h)
	{
		x = 0;
		while (game->map->map[y][x] != '\0')
		{
			if (game->map->map[y][x] == 'C')
			{
				game->sprites[game->sprite_count].x = x + 0.5;
				game->sprites[game->sprite_count].y = y + 0.5;
				game->sprites[game->sprite_count].current_frame = 0;
				game->sprite_count++;
			}
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_game		game;
	t_player	player;

	if (argc != 2)
		return (putstr_fd("Error!\nUsage: ./cub3d <map_file.cub>\n", 2), 1);
	if (!check_filename(argv[1]))
		return (putstr_fd("Error: Invalid file format, only .cub file\n", 2),
			1);
	init_map(&map);
	map_check(argv, &map);
	if (init_win(&game, &map, &player) == 1)
		close_window(&game);
	find_sprites(&game);
	set_dir(&game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, handle_down, &game);
	mlx_hook(game.win, ON_KEYUP, 1L << 1, handle_up, &game);
	mlx_loop_hook(game.mlx, update_game, &game);
	mlx_hook(game.win, ON_DESTROY, 1L << 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
