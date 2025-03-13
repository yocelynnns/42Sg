/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:52:58 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/14 01:34:51 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() {}

void Zombie::setName(std::string name) {
    Name = name;
}

void Zombie::announce() {
    std::cout << Name << ": BraiiiiiiinnnzzzZ..." << std::endl;
};

Zombie::~Zombie() {
    std::cout << Name << " is destroyed." << std::endl;
}