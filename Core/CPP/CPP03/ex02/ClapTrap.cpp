/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:45:48 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/05 17:21:02 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name) {
    this->Name = name;
    this->HitPts = 10;
    this->EnergyPts = 10;
    this->AttackDmg = 0;
    std::cout << "ClapTrap " << this->Name << " is created." << std::endl;
}

void ClapTrap::attack(const std::string& target) {
    if (this->HitPts < 1) {
        std::cout << "ClapTrap " << this->Name << " is dead and cannot attack." << std::endl;
        return ;
    }
    if (this->EnergyPts < 1) {
        std::cout << "ClapTrap " << this->Name << " does not have enough energy to attack." << std::endl;
        return ;
    }
    std::cout << "ClapTrap " << this->Name << " attacks " << target << ", causing " << this->AttackDmg << " points of damage!" << std::endl;
    this->EnergyPts -= 1;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (this->HitPts < 1) {
        std::cout << "ClapTrap " << this->Name << " is already dead." << std::endl;
        return ;
    }
    std::cout << "ClapTrap " << this->Name << " takes " << amount << " points of damage!" << std::endl;
    this->HitPts -= (int)amount;
    if (this->HitPts < 1) {
        std::cout << "ClapTrap " << this->Name << " has died." << std::endl;
        return ;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->HitPts < 1) {
        std::cout << "ClapTrap " << this->Name << " is dead and cannot be repaired." << std::endl;
        return ;
    }
    if (this->EnergyPts < 1) {
        std::cout << "ClapTrap " << this->Name << " does not have enough energy to be repaired." << std::endl;
        return ;
    }
    std::cout << "ClapTrap " << this->Name << " is repaired for " << amount << " points of health!" << std::endl;
    this->HitPts += (int)amount;
    this->EnergyPts -= 1;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << this->Name << " is destroyed." << std::endl;
}