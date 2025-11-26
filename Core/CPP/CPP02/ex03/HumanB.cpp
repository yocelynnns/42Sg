/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:05:09 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/20 16:37:41 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : Name(name) {}

void HumanB::attack() {
    if (weapon) {
        std::cout << Name << " attacks with their " << weapon->getType() << std::endl;
    } else {
        std::cout << Name << " has no weapon!" << std::endl;
    }
};

void HumanB::setWeapon(Weapon &weapon){
    this->weapon = &weapon;
}