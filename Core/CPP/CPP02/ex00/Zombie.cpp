/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:40:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/19 02:03:30 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) {
    Name = name;
}

void Zombie::Announce() {
    std::cout << Name << ": BraiiiiiiinnnzzzZ..." << std::endl;
};

Zombie::~Zombie() {
    std::cout << Name << " is destroyed." << std::endl;
}
