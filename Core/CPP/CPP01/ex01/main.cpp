/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:53:02 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/14 01:30:37 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    int N = 5;
    std::string Name = "Foo";

    Zombie *horde = zombieHorde(Name, N);

    if (horde) {
        for (int i = 0; i < N; ++i) {
            horde[i].announce();
        }
        delete[] horde;
    }
    
    return 0;
}