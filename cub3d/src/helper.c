#include "cub3d.h"

int check_filename(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strcmp(&filename[len - 4], ".cub") == 0);
}

int ends_with_xpm(char *path)
{
	int len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

