/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:12:47 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/10/22 18:00:08 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_dimension(t_struct *m_structs)
{
	m_structs->map_w = ft_strlen(m_structs->map[0]);
	m_structs->map_h = 0;
	while (m_structs->map[m_structs->map_h])
		m_structs->map_h++;
}

int rect_check(t_struct *m_struct)
{
    int	y;

	y = 0;
	while (y < m_struct->map_h)
	{
		if (ft_strlen(m_struct->map[y]) != m_struct->map_w)
			return (0);
		y++;
	}
	return (1);
}

int wall_check(t_struct *m_struct)
{
    int x;
    int y;

    x = 0;
    while (x < m_struct->map_w)
    {
        if (m_struct->map[0][x] != '1' || m_struct->map[m_struct->map_h - 1][x] != '1')
            return (0);
        x++;
    }
    y = 1;
    while (y < m_struct->map_h - 1)
    {
        if (m_struct->map[y][0] != '1' || m_struct->map[y][m_struct->map_w - 1] != '1')
            return (0);
        y++;
    }
    return (1);
}
