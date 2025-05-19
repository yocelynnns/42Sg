/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:12:31 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/19 16:52:27 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_map map;
	t_game game;
	t_player player;

	if (argc != 2)
		return (printf("Error!\nUsage: ./cub3d <map_file.cub>\n"), 1);
	if (!check_filename(argv[1]))
		return (printf("Error: Invalid file format, only .cub file\n"), 1);
	init_map(&map);
	map_check(argv, &map);
	if (init_win(&game, &map, &player) == 1)
		exit(1);
	set_dir(&game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, handle_down, &game);
	mlx_hook(game.win, ON_KEYUP, 1L << 1, handle_up, &game);
	mlx_loop_hook(game.mlx, update_game, &game);
	mlx_hook(game.win, ON_DESTROY, 1L << 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
