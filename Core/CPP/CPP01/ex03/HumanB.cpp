/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:05:09 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/17 18:28:56 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : Name(name) {}

void HumanB::attack() {
    std::cout << Name << " attacks with their " << weapon->getType() << std::endl;
};

void HumanB::setWeapon(Weapon &weapon){
    this->weapon = &weapon;
}