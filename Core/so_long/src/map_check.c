/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:12:47 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/10/25 01:12:08 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

void	map_dimension(t_map *map_s)
{
	map_s->map_w = ft_strlen(map_s->map[0]);
	map_s->map_h = 0;
	while (map_s->map[map_s->map_h])
		map_s->map_h++;
}

int	rect_check(t_map *map_s)
{
	int	y;

	y = 0;
	while (y < map_s->map_h)
	{
		if (ft_strlen(map_s->map[y]) != map_s->map_w)
			return (0);
		y++;
	}
	return (1);
}

int	wall_check(t_map *map_s)
{
	int	x;
	int	y;

	x = 0;
	while (x < map_s->map_w)
	{
		if (map_s->map[0][x] != '1' || \
		map_s->map[map_s->map_h - 1][x] != '1')
			return (0);
		x++;
	}
	y = 1;
	while (y < map_s->map_h - 1)
	{
		if (map_s->map[y][0] != '1' || \
		map_s->map[y][map_s->map_w - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}
