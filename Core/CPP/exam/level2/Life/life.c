/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:58:48 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/16 13:15:45 by yocelynnns       ###   ########.fr       */
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
                if (nx >= 0 && ny >= 0 && nx < life->w && ny < life->h)
                    if (life->board[ny * life->w + nx])
                        count++;
            }
            ++dx;
        }
        ++dy;
    }
    return count;
}

void solve_map(t_life *life)
{
    char *next = (char *)calloc(life->w * life->h, sizeof(char));
    int y = 0;
    while (y < life->h)
    {
        int x = 0;
        while (x < life->w)
        {
            int idx = y * life->w + x;
            int n = count_neighbors(life, x, y);
            if (life->board[idx])
            {
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
    while (i < life->w * life->h)
    {
        life->board[i] = next[i];
        ++i;
    }
    free(next);
}

void print_map(t_life *life)
{
    int y = 0;
    while (y < life->h)
    {
        int x = 0;
        while (x < life->w)
        {
            if (life->board[y * life->w + x])
                putchar('O');
            else
                putchar(' ');
            ++x;
        }
        putchar('\n');
        ++y;
    }
}

void input_char(t_life *life)
{
    char buf[1];
    while (read(0, buf, 1) > 0)
    {
        char c = buf[0];
        if (c == 'x')
        {
            life->draw = !life->draw;
            if (life->draw)
                life->board[life->y * life->w + life->x] = 1;
        }
        else if (c == 'w' && life->y > 0)
            life->y--;
        else if (c == 's' && life-> y < life->h - 1)
            life->y++;
        else if (c == 'a' && life->x > 0)
            life->x--;
        else if (c == 'd' && life->x < life->w - 1)
            life->x++;
        if (life->draw)
            life->board[life->y * life->w + life->x] = 1;
    }
}

int main (int argc, char **argv)
{
    if (argc != 4)
        return 1;
    
    t_life life;
    life.w = atoi(argv[1]);
    life.h = atoi(argv[2]);
    int iter = atoi(argv[3]);

    life.board = (char *)calloc(life.w * life.h, sizeof(char));
    life.x = 0;
    life.y = 0;
    life.draw = 0;

    input_char(&life);
    while (iter-- > 0)
        solve_map(&life);
    print_map(&life);
    free(life.board);
    return 0;
}