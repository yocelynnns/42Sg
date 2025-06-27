/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:47:18 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/26 16:12:28 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int count_neighbors(t_life *life, int x, int y)
{
    int count = 0;
    int dy = -1;
    while (dy <= 1)
    {
        int dx = -1;
        while (dx <= 1)
        {
            if (!(dx == 0 && dy == 0))
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < life->width && ny >= 0 && ny < life->height) {
                    if (life->board[ny * life->width + nx])
                        count++;
                }
            }
            ++dx;
        }
        ++dy;
    }
    return count;
}

void simulate(t_life *life)
{
    char *next = (char *)calloc(life->width * life->height, sizeof(char));
    int y = 0;
    while (y < life->height)
    {
        int x = 0;
        while (x < life->width)
        {
            int idx = y * life->width + x;
            int n = count_neighbors(life, x, y);
            if (life->board[idx]) {
                if (n == 2 || n == 3)
                    next[idx] = 1;
            } else {
                if (n == 3)
                    next[idx] = 1;
            }
            ++x;
        }
        ++y;
    }
    int i = 0;
    while (i < life->width * life->height)
    {
        life->board[i] = next[i];
        ++i;
    }
    free(next);
}

void print_board(t_life *life)
{
    int y = 0;
    while (y < life->height)
    {
        int x = 0;
        while (x < life->width)
        {
            char c;
            if (life->board[y * life->width + x]) {
                c = '0';
            } else {
                c = ' ';
            }
            write(1, &c, 1);
            ++x;
        }
        write(1, "\n", 1);
        ++y;
    }
}

void draw_input(t_life *life)
{
    char buf[1];
    while (read(0, buf, 1) > 0)
    {
        char c = buf[0];
        if (c == 'x')
        {
            life->drawing = !life->drawing;
            if (life->drawing)
                life->board[life->y * life->width + life->x] = 1;
        }
        else if (c == 'w' && life->y > 0)
            life->y--;
        else if (c == 's' && life->y < life->height - 1)
            life->y++;
        else if (c == 'a' && life->x > 0)
            life->x--;
        else if (c == 'd' && life->x < life->width - 1)
            life->x++;
        if (life->drawing)
            life->board[life->y * life->width + life->x] = 1;
    }
}
