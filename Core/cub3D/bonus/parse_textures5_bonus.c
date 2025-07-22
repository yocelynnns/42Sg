/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:46:32 by nsan              #+#    #+#             */
/*   Updated: 2025/05/22 20:21:22 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_floor(t_map *map, char *line)
{
	if (map->has_floor)
		return (0);
	map->has_floor = true;
	return (parse_color(map->floor_rgb, line + 2));
}

int	handle_ceiling(t_map *map, char *line)
{
	if (map->has_ceiling)
		return (0);
	map->has_ceiling = true;
	return (parse_color(map->ceiling_rgb, line + 2));
}

int	handle_door(t_map *map, char *line)
{
	if (map->has_door)
		return (0);
	map->has_door = true;
	return (set_texture_path(&map->door_path, line + 2));
}

int	parse_texture_color(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (handle_no(map, line));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (handle_so(map, line));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (handle_ea(map, line));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (handle_we(map, line));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (handle_floor(map, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (handle_ceiling(map, line));
	if (ft_strncmp(line, "D ", 2) == 0)
		return (handle_door(map, line));
	return (0);
}
