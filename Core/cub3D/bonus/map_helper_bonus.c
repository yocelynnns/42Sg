/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:47:36 by nsan              #+#    #+#             */
/*   Updated: 2025/05/26 15:51:17 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_full_buffer(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	char	*result;
	int		bytes;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		temp = ft_strjoin(result, buf);
		free(result);
		result = temp;
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes == -1)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char	**duplicate_map(char **map)
{
	int		i;
	char	**dup;

	i = 0;
	while (map[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (map[i])
	{
		dup[i] = ft_strdup(map[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	add_line_to_map(t_map *map, char *line)
{
	int		i;
	char	**new_map;

	i = 0;
	while (map->map && map->map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		ft_error("Malloc failed", map);
	i = 0;
	while (map->map && map->map[i])
	{
		new_map[i] = map->map[i];
		i++;
	}
	new_map[i++] = ft_strdup(line);
	new_map[i] = NULL;
	free(map->map);
	map->map = new_map;
}

int	open_map_file(t_map *map, char **argv)
{
	map->map_fd = open(argv[1], O_RDONLY);
	if (map->map_fd == -1)
		return (putstr_fd("Error: Could not open .cub file\n", 2), 0);
	return (1);
}
