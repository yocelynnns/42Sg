/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:52:53 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/19 02:04:38 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *ZombieHorde(std::string name, int n)
{
    if (n <= 0)
    return NULL;

    Zombie *horde = new Zombie[n];

    for (int i = 0; i < n; ++i) {
        horde[i].SetName(name);
    }
    return horde;
}
