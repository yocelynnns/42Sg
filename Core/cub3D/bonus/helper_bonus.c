/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:09 by nsan              #+#    #+#             */
/*   Updated: 2025/05/22 20:22:07 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strcmp(&filename[len - 4], ".cub") == 0);
}

int	ends_with_xpm(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}
