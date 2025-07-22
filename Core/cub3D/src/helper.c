/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:54:52 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/19 20:59:37 by yocelynnns       ###   ########.fr       */
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
