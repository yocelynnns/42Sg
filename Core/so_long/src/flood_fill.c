/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:48:50 by ysetiawa          #+#    #+#             */
/*   Updated: 2024/10/22 20:09:30 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	floodfill(t_struct *m_struct, int y, int x, t_temp *temp)
{
	if (y < 0 || y >= m_struct->map_h || x < 0 || x >= m_struct->map_w || m_struct->map_cp[y][x] == '1' || m_struct->map_cp[y][x] == 'F')
        return;
	if (m_struct->map_cp[y][x] == 'C')
		temp->c--;
	if (m_struct->map_cp[y][x] == 'E')
		temp->e--;
	m_struct->map_cp[y][x] = 'F';
	floodfill(m_struct, y + 1, x, temp);
	floodfill(m_struct, y - 1, x, temp);
	floodfill(m_struct, y, x + 1, temp);
	floodfill(m_struct, y, x - 1, temp);
}

void startfill(t_struct *m_struct)
{
    t_temp temp;

    temp.c = m_struct->collect;
    temp.e = m_struct->exit;

    floodfill(m_struct, m_struct->player_y, m_struct->player_x, &temp);
	if (!map_valid(&temp))
		ft_error("Error: Not all collectibles and exits have been reached.\n", m_struct);
}

int map_valid(t_temp *temp)
{
    if (temp->c == 0 && temp->e == 0)
        return (1);
    return (0);
}
