/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:55:17 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/25 17:01:00 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_int(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	safe_atoi(const char *str, int *result)
{
	long	val;

	val = ft_atol(str);
	if (val < 0 || val > 255)
		return (0);
	*result = (int)val;
	return (1);
}

int	parse_color(int *color_array, char *str)
{
	char	**values;
	int		i;
	int		value;

	values = ft_split(str, ',');
	if (!values)
		return (0);
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
		return (free_arr(values), 0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_int(values[i]) || !safe_atoi(values[i], &value))
			return (free_arr(values), 0);
		color_array[i] = value;
		i++;
	}
	free_arr(values);
	return (1);
}

int	set_texture_path(char **path, char *line)
{
	*path = ft_strtrim(line, " \n");
	if (!ends_with_xpm(*path))
	{
		free(*path);
		*path = NULL;
		return (0);
	}
	return (1);
}
