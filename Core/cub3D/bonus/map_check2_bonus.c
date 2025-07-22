/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:02:45 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/23 16:07:56 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_player_to_door(t_game *game)
{
	int	i;
	int	px;
	int	py;
	int	dx;
	int	dy;

	i = 0;
	px = (int)game->p->x;
	py = (int)game->p->y;
	game->player_next_to_door = 0;
	while (i < game->map->door_count)
	{
		dx = game->map->doors[i].door_x;
		dy = game->map->doors[i].door_y;
		if ((px == dx && (py == dy - 1 || py == dy + 1))
			|| (py == dy && (px == dx - 1 || px == dx + 1)))
		{
			game->player_next_to_door = 1;
			return ;
		}
		i++;
	}
}

void	floodfill(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->map_h || x < 0
		|| x >= (int)ft_strlen(map->map_cp[y]))
		ft_error("Error: Map is not enclosed (out of bounds).\n", map);
	if (map->map_cp[y][x] == ' ' || map->map_cp[y][x] == '\0'
		|| map->map_cp[y][x] == '\n')
		ft_error("Error: Map is not enclosed (space or null).\n", map);
	if (map->map_cp[y][x] == '1' || map->map_cp[y][x] == 'F' ||
		map->map_cp[y][x] == 'D')
		return ;
	map->map_cp[y][x] = 'F';
	floodfill(map, y + 1, x);
	floodfill(map, y - 1, x);
	floodfill(map, y, x + 1);
	floodfill(map, y, x - 1);
}

void	map_check(char **argv, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	if (!read_map(map, argv))
		ft_error("", map);
	map_dimension(map);
	if (!valid_elements(map))
		ft_error("Error: Invalid elements in the map.\n", map);
	count_and_check_player(map);
	while (map->map_cp[y])
	{
		x = 0;
		while (map->map_cp[y][x])
		{
			if (!(map->map_cp[y][x] == 1)
			&& !(map->map_cp[y][x] == ' '))
				floodfill(map, y, x);
			x++;
		}
		y++;
	}
	check_door_location(map);
}
