/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:47:53 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/26 14:59:46 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int main(int ac, char **av) {
    if (ac != 4)
        return 1;

    t_life life;
    life.width = atoi(av[1]);
    life.height = atoi(av[2]);
    int iterations = atoi(av[3]);

    if (life.width <= 0 || life.height <= 0 || iterations < 0)
        return 1;

    life.board = (char *)calloc(life.width * life.height, sizeof(char));
    life.x = 0;
    life.y = 0;
    life.drawing = 0;

    draw_input(&life);
    while (iterations-- > 0)
        simulate(&life);
    print_board(&life);
    free(life.board);
    return 0;
}
