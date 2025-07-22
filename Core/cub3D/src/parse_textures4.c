/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:00:23 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/25 17:08:54 by ysetiawa         ###   ########.fr       */
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
	return (0);
}
