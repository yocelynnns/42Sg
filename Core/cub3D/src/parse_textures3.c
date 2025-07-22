/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:59:41 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/25 17:00:31 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_no(t_map *map, char *line)
{
	if (map->has_no)
		return (0);
	map->has_no = true;
	return (set_texture_path(&map->no_path, line + 3));
}

int	handle_so(t_map *map, char *line)
{
	if (map->has_so)
		return (0);
	map->has_so = true;
	return (set_texture_path(&map->so_path, line + 3));
}

int	handle_ea(t_map *map, char *line)
{
	if (map->has_ea)
		return (0);
	map->has_ea = true;
	return (set_texture_path(&map->ea_path, line + 3));
}

int	handle_we(t_map *map, char *line)
{
	if (map->has_we)
		return (0);
	map->has_we = true;
	return (set_texture_path(&map->we_path, line + 3));
}
