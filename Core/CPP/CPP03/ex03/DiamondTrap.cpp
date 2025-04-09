/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:25:29 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/05 22:58:08 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), Name(name) {
    this->HitPts = FragTrap::HitPts;
    this->EnergyPts = ScavTrap::EnergyPts;
    this->AttackDmg = FragTrap::AttackDmg;
    std::cout << "DiamondTrap " << this->Name << " is created." << std::endl;
}

void DiamondTrap::whoAmI(void) {
    std::cout << "I am " << this->Name << ", and my ClapTrap name is " << ClapTrap::Name << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target);
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap " << this->Name << " is destroyed." << std::endl;
}
