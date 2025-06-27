/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:53:00 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 17:49:35 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    Bsq bsq;
    if (!load_map(&bsq, argv[1]))
        return 1;

    solve_bsq(&bsq);
    print_map(&bsq);
    free_bsq(&bsq);

    return 0;
}
