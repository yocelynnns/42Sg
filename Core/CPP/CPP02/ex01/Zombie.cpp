/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:52:58 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/19 02:03:17 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() {}

void Zombie::SetName(std::string name) {
    Name = name;
}

void Zombie::Announce() {
    std::cout << Name << ": BraiiiiiiinnnzzzZ..." << std::endl;
};

Zombie::~Zombie() {
    std::cout << Name << " is destroyed." << std::endl;
}