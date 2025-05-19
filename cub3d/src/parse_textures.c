#include "cub3d.h"

int parse_color(int *color_array, char *str)
{
	char **values;
	int i;

	values = ft_split(str, ',');
	if (!values)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!values[i])
			return (free_arr(values), 0);
		color_array[i] = ft_atoi(values[i]);
		if (color_array[i] < 0 || color_array[i] > 255)
			return (free_arr(values), 0);
		i++;
	}
	free_arr(values);
	return (1);
}

int set_texture_path(char **path, char *line)
{
	*path = ft_strtrim(line, " \n");
	if (!ends_with_xpm(*path))
	{
		free(*path);
		return (0);
	}
	return (1);
}

int parse_texture_color(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture_path(&map->no_path, line + 3));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture_path(&map->so_path, line + 3));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture_path(&map->ea_path, line + 3));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture_path(&map->we_path, line + 3));
	else if (ft_strncmp(line, "D ",2) == 0)
		return (set_texture_path(&map->door_path, line + 2));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(map->floor_rgb, line + 2));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(map->ceiling_rgb, line + 2));
	else
		return (0);
	return (1);
}

