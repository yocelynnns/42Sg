#include "cub3d.h"

char *get_full_buffer(int fd)
{
	char buf[BUFFER_SIZE];
	char *temp;
	char *result;
	int bytes;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		temp = ft_strjoin(result, buf);
		free(result);
		result = temp;
	}
	if (bytes == -1)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char **duplicate_map(char **map)
{
	int i = 0;
	char **dup;

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

void add_line_to_map(t_map *map, char *line)
{
	int i;
	char **new_map;

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

int read_map(t_map *map, char **argv)
{
	char *buffer;
	char **lines;
	int i;
	int map_started;

	i = 0;
	map_started = 0;
	map->map_fd = open(argv[1], O_RDONLY);
	if (map->map_fd == -1)
		return (perror("Error: Could not open .cub file"), 0);
	buffer = get_full_buffer(map->map_fd);
	if (!buffer)
		return (close(map->map_fd), 0);
	lines = ft_split(buffer, '\n');
	free(buffer);
	close(map->map_fd);
	if (!lines)
		return (printf("Error: Split failed.\n"), 0);
	while (lines[i])
	{
		if (!map_started)
		{
			if (!parse_texture_color(map, lines[i]))
			{
				if (is_map_line(lines[i]))
					map_started = 1;
				else
					return (free_arr(lines), printf("Error: Invalid identifier\n"), 0);
			}	
		}
		if (map_started)
			add_line_to_map(map, lines[i]);
		i++;
	}
	free_arr(lines);
	if (!map->map)
		return (printf("Error: Map is missing.\n"), 0);
	map->map_cp = duplicate_map(map->map);
	return (map->map_cp != NULL);
}

int is_map_line(char *line)
{
	while (*line == ' ')
		line++;
	return (*line == '0' || *line == '1');
}