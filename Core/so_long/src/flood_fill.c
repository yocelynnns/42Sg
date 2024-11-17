/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:50 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/25 01:12:08 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "so_long.h"

void	floodfill(t_map *map_s, int y, int x, t_temp *temp)
{
	if (y < 0 || y >= map_s->map_h || x < 0 || x >= map_s->map_w \
	|| map_s->map_cp[y][x] == '1' || map_s->map_cp[y][x] == 'F')
		return ;
	if (map_s->map_cp[y][x] == 'C')
		temp->c--;
	if (map_s->map_cp[y][x] == 'E')
		temp->e--;
	map_s->map_cp[y][x] = 'F';
	floodfill(map_s, y + 1, x, temp);
	floodfill(map_s, y - 1, x, temp);
	floodfill(map_s, y, x + 1, temp);
	floodfill(map_s, y, x - 1, temp);
}

void	startfill(t_map *map_s)
{
	t_temp	temp;

	temp.c = map_s->collect;
	temp.e = map_s->exit;
	floodfill(map_s, map_s->player_y, map_s->player_x, &temp);
	if (!map_valid(&temp))
		ft_error("Error: Collectibles or exits not reached.\n", map_s);
}

int	map_valid(t_temp *temp)
{
	if (temp->c == 0 && temp->e == 0)
		return (1);
	return (0);
}
