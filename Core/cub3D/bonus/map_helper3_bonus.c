/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:14:04 by nsan              #+#    #+#             */
/*   Updated: 2025/05/25 18:48:13 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_elements(t_map *map)
{
	if (!map->has_no || !map->has_so || !map->has_ea || !map->has_we)
	{
		putstr_fd("Error: Missing one or more texture paths (NO, SO, EA, WE)\n",
			2);
		return (0);
	}
	if (!map->has_floor || !map->has_ceiling)
	{
		putstr_fd("Error: Missing floor (F) or ceiling (C)\n", 2);
		return (0);
	}
	return (1);
}

int	handle_identifier(t_map *map, char *line, int *started, char **lines)
{
	if (is_map_line(line))
	{
		if (!check_elements(map))
			return (free_arr(lines), 0);
		*started = 1;
	}
	else
	{
		putstr_fd("Error: Invalid identifier\n", 2);
		return (free_arr(lines), 0);
	}
	return (1);
}

int	process_lines(t_map *map, char **lines)
{
	int	i;
	int	started;

	i = 0;
	started = 0;
	while (lines[i])
	{
		if (!started && !parse_texture_color(map, lines[i]))
		{
			if (!handle_identifier(map, lines[i], &started, lines))
				return (0);
		}
		if (started)
			add_line_to_map(map, lines[i]);
		i++;
	}
	return (1);
}
