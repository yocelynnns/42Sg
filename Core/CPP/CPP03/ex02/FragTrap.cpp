/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:51:35 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/05 22:22:53 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    this->HitPts = 100;
    this->EnergyPts = 100;
    this->AttackDmg = 30;
    std::cout << "FragTrap " << this->Name << " is created." << std::endl;
}

void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << this->Name << " requested a high five." << std::endl;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap " << this->Name << " is destroyed." << std::endl;
}

// void FragTrap::attack(const std::string& target) {
//     std::cout << "[FragTrap] ";
//     ClapTrap::attack(target);
// }
