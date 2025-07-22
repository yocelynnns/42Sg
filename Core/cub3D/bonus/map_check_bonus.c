/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 01:02:21 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/23 16:06:07 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_elements(t_map *map)
{
	int	y;
	int	x;
	int	c;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			c = map->map[y][x];
			if (c != '1' && c != '0' && c != ' ' && c != 'C'
				&& c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'D')
				return (0);
			if (c == 'D')
				map->door_count++;
		}
	}
	if (!map->door_count)
		ft_error("Error: Doors missing!\n", map);
	return (1);
}

void	map_dimension(t_map *map)
{
	int	max_width;
	int	i;
	int	current_len;

	max_width = 0;
	i = 0;
	while (map->map[i])
	{
		current_len = ft_strlen(map->map[i]);
		if (current_len > max_width)
			max_width = current_len;
		i++;
	}
	map->map_w = max_width;
	map->map_h = i;
}

void	count_and_check_player(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			c = map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				map->p_count++;
				map->player_x = x + 0.5;
				map->player_y = y + 0.5;
				map->player_dir = c;
			}
		}
	}
	if (map->p_count != 1)
		ft_error("Error: Invalid number of players\n", map);
}
