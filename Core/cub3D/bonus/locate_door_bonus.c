/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:41:53 by nsan              #+#    #+#             */
/*   Updated: 2025/05/22 20:23:15 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scan_map_for_doors(t_map *map, t_door *doors)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < map->map_h)
	{
		j = 0;
		while (map->map_cp[i][j] != '\0')
		{
			if (map->map_cp[i][j] == 'D')
			{
				doors[k].door_x = j;
				doors[k].door_y = i;
				doors[k].door_state = 0;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	check_door_location(t_map *map)
{
	t_door	*doors;

	doors = malloc(sizeof(t_door) * map->door_count);
	if (!doors)
		return ;
	scan_map_for_doors(map, doors);
	map->doors = doors;
}
