/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:02:45 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/14 18:18:21 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map_cp(char **map_cp)
{
	int	i;

	i = 0;

	while (map_cp && map_cp[i])
	{
		printf("%s\n", map_cp[i]);
		i++;
	}
}

void	check_door_location(t_map *map)
{
	int 	i;
	int 	j;
	int 	k;
	t_door *doors;

	k = 0;
	i = 0;
	j = 0;

	print_map_cp(map->map_cp);
	printf("check door location\n");
	doors = malloc(sizeof(t_door) * map->door_count);
	if (!doors)
		return ;
	printf("map height -> %d \n", map->map_h);
	printf("map width -> %d \n", map->map_w);
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			// printf("i -> %d, j => %d\n", i, j);
			if (map->map_cp[i][j] == '\n')
				break ;
			if (map->map_cp[i][j] == 'D')
			{
				doors[k].door_x = j;
				doors[k].door_y = i;
				doors[k].door_state = 0;
				k++;
				printf("door location -> %d, %d\n", i, j);
			}
			j++;
		}
		i++;
	}
	map->doors = doors;
}


void check_player_to_door(t_game *game)
{
	int i;
	int	px;
	int	py;
	int	dx;
	int	dy;

	i = 0;
	px = (int)game->p->x;
	py = (int)game->p->y;
	game->player_next_to_door = 0; // reset each frame
	while (i < game->map->door_count)
	{
		dx = game->map->doors[i].door_x;
		dy = game->map->doors[i].door_y;
		if ((px == dx && (py == dy - 1 || py == dy + 1)) ||
			(py == dy && (px == dx - 1 || px == dx + 1)))
		{
			game->player_next_to_door = 1; 
			return ;
		}
		i++;
	}
}

void	floodfill(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->map_h || x < 0 || x >= (int)ft_strlen(map->map_cp[y]))
		ft_error("Error: Map is not enclosed (out of bounds).\n", map);
	if (map->map_cp[y][x] == ' ' || map->map_cp[y][x] == '\0')
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
			&& !(map->map_cp[y][x]== ' '))
				floodfill(map, y, x);
			if (map->map_cp[y][x] == 'D')
				map->door_count++;	
			x++;
		}
		y++;
	}
	printf("no. of doors -> %d \n", map->door_count);
	check_door_location(map);
}
