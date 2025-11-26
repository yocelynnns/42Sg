/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:55:13 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 19:17:53 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_lines_from_buffer(t_map *map)
{
	char	*buffer;
	char	**lines;

	buffer = get_full_buffer(map->map_fd);
	if (!buffer)
		return (close(map->map_fd), NULL);
	lines = ft_split(buffer, '\n');
	free(buffer);
	close(map->map_fd);
	return (lines);
}

int	read_map(t_map *map, char **argv)
{
	char	**lines;

	if (!open_map_file(map, argv))
		return (0);
	lines = get_lines_from_buffer(map);
	if (!lines)
		return (putstr_fd("Error: Split failed.\n", 2), 0);
	if (!process_lines(map, lines))
		return (0);
	free_arr(lines);
	if (!map->map)
		return (putstr_fd("Error: Map is missing.\n", 2), 0);
	map->map_cp = duplicate_map(map->map);
	return (map->map_cp != NULL);
}

int	is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '0' || *line == '1');
}

// int	determine_gap(char *buffer, int map_start)
// {
// 	int	i;

// 	i = map_start;
// 	while (buffer[i])
// 	{
// 		if (buffer[i] == '\n')
// 		{
// 			if (buffer[i + 1] == '\n')
// 				return (putstr_fd("Gap not allowed in map\n", 2), 0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int	start_pos(char *buffer)
// {
// 	int	i;
// 	int	j;
// 	int	map_start;
// 	int	has_start;

// 	has_start = 0;
// 	i = 0;
// 	while (buffer[i])
// 	{
// 		if (buffer[i] == '1')
// 		{
// 			j = 1;
// 			while (j <= 3)
// 			{
// 				if (buffer[i + j] == '1')
// 					has_start = 1;
// 				map_start = i;
// 				j++;
// 			}
// 		}
// 		if (has_start)
// 			break ;
// 		i++;
// 	}
// 	return (map_start);
// }