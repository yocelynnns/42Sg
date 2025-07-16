/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:58:51 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/16 13:16:18 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_life {
    char *board;
    int w;
    int h;
    int x;
    int y;
    int draw;
} t_life;

#endif