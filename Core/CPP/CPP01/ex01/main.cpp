/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:53:02 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/19 02:04:23 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    int N = 5;
    std::string Name = "Foo";

    Zombie *horde = ZombieHorde(Name, N);

    if (horde) {
        for (int i = 0; i < N; ++i) {
            horde[i].Announce();
        }
        delete[] horde;
    }
    
    return 0;
}