/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:49:03 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 17:49:04 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **map;
    int **dp;
    int rows;
    int cols;
} Bsq;

int load_map(Bsq *bsq, const char *filename);
void solve_bsq(Bsq *bsq);
void print_map(Bsq *bsq);
void free_bsq(Bsq *bsq);

#endif
