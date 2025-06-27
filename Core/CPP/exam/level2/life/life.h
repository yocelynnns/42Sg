/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:46:57 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/26 15:10:18 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>

typedef struct s_life {
    char *board;
    int width;
    int height;
    int x;
    int y;
    int drawing;
} t_life;

void draw_input(t_life *life);
void simulate(t_life *life);
void print_board(t_life *life);
int count_neighbors(t_life *life, int x, int y);

#endif
