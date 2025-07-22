/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:02:45 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 18:11:08 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floodfill(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->map_h || x < 0 || x
		>= (int)ft_strlen(map->map_cp[y]))
		ft_error("Error: Map is not enclosed (out of bounds).\n", map);
	if (map->map_cp[y][x] == ' ' || map->map_cp[y][x] == '\0')
		ft_error("Error: Map is not enclosed (space or null).\n", map);
	if (map->map_cp[y][x] == '1' || map->map_cp[y][x] == 'F')
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
			if (!(map->map_cp[y][x] == 1) && !(map->map_cp[y][x] == ' '))
				floodfill(map, y, x);
			x++;
		}
		y++;
	}
}
