/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:40:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/14 01:23:15 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) {
    Name = name;
}

void Zombie::announce() {
    std::cout << Name << ": BraiiiiiiinnnzzzZ..." << std::endl;
};

Zombie::~Zombie() {
    std::cout << Name << " is destroyed." << std::endl;
}
