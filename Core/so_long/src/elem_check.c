/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:30:08 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/10/25 23:38:33 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

void	count_elems(t_map *map_s)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < map_s->map_h)
	{
		x = 0;
		while (x < map_s->map_w)
		{
			c = map_s->map[y][x];
			if (c == 'C')
				map_s->collect++;
			else if (c == 'E')
				map_s->exit++;
			else if (c == 'P')
			{
				map_s->player++;
				map_s->player_x = x;
				map_s->player_y = y;
			}
			x++;
		}
		y++;
	}
}

int	valid_elem(t_map *map_s)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < map_s->map_h)
	{
		x = 0;
		while (x < map_s->map_w)
		{
			c = map_s->map[y][x];
			if (c != '1' && c != '0' && c != 'C' && c != 'E' && c != 'P')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	check_elem(t_map *map_s)
{
	if (map_s->player != 1)
		ft_error("Error: Map must only have 1 player.\n", map_s);
	if (map_s->collect < 1)
		ft_error("Error: Map must have at least 1 collectible.\n", map_s);
	if (map_s->exit != 1)
		ft_error("Error: Map must only have 1 exit.\n", map_s);
}
