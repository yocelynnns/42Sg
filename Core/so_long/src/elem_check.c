/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:30:08 by yocelynnns        #+#    #+#             */
/*   Updated: 2024/10/22 20:18:39 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void count_elems(t_struct *m_struct)
{
    int x;
    int y;
    char c;

    y = 0;
    while (y < m_struct->map_h)
    {
        x = 0;
        while (x < m_struct->map_w)
        {
            c = m_struct->map[y][x];
            if (c == 'C')
                m_struct->collect++;
            else if (c == 'E')
                m_struct->exit++;
            else if (c == 'P')
            {
                m_struct->player++;
                m_struct->player_x = x;
                m_struct->player_y = y;
            }
            x++;
        }
        y++;
    }
}

int valid_elem(t_struct *m_struct)
{
    int x;
    int y;
    char c;

    y = 0;
    while (y < m_struct->map_h)
    {
        x = 0;
        while (x < m_struct->map_w)
        {
            c = m_struct->map[y][x];
            if (c != '1' && c != '0' && c != 'C' && c != 'E' && c != 'P')
                return (0);
            x++;
        }
        y++;
    }
    return (1);
}

void check_elem(t_struct *m_struct)
{
    if (m_struct->player != 1)
        ft_error("Map must only have 1 player.\n", m_struct);
    if (m_struct->collect < 1)
        ft_error("Map must have at least 1 collectible.\n", m_struct);
    if (m_struct->exit != 1)
        ft_error("Map must only have 1 exit.\n", m_struct);
}
