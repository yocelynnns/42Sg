/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:25:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/05 22:02:25 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    this->HitPts = 100;
    this->EnergyPts = 50;
    this->AttackDmg = 20;
    std::cout << "ScavTrap " << this->Name << " is created." << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    std::cout << "[ScavTrap] ";
    ClapTrap::attack(target);
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << this->Name << " is now in Gate Keeper mode." << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << this->Name << " is destroyed." << std::endl;
}

// void ScavTrap::attack(const std::string& target) {
//     if (this->HitPts < 1) {
//         std::cout << "ScavTrap " << this->Name << " is dead and cannot attack." << std::endl;
//         return ;
//     }
//     if (this->EnergyPts < 1) {
//         std::cout << "ScavTrap " << this->Name << " does not have enough energy to attack." << std::endl;
//         return ;
//     }
//     std::cout << "ScavTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDmg << " points of damage!" << std::endl;
//     this->EnergyPts -= 1;
// }
