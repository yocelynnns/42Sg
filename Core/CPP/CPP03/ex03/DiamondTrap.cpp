/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:25:29 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 00:25:09 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

// Default constructor
DiamondTrap::DiamondTrap()
: ClapTrap("DefaultDiamond_clap_name"), ScavTrap("DefaultDiamond"), FragTrap("DefaultDiamond"), name("DefaultDiamond")
{
    hitPts = FragTrap::hitPts;
    energyPts = ScavTrap::energyPts;
    attackDmg = FragTrap::attackDmg;
    maxHitPts = FragTrap::hitPts;
    std::cout << "DiamondTrap " << name << " is created (default)." << std::endl;
}

// Custom constructor
DiamondTrap::DiamondTrap(std::string name)
: ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), name(name)
{
    hitPts = 100;
    energyPts = 50;
    attackDmg = 30;
    maxHitPts = 100;
    std::cout << "DiamondTrap " << name << " is created." << std::endl;
}

// Copy constructor
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other);
        ScavTrap::operator=(other);
        FragTrap::operator=(other);
        this->name = other.name;
    }
    std::cout << "DiamondTrap " << name << " is assigned." << std::endl;
    return *this;
}

// Copy assignment operator
DiamondTrap::DiamondTrap(const DiamondTrap& other)
    : ClapTrap(other), ScavTrap(other), FragTrap(other), name(other.name) {
    std::cout << "DiamondTrap " << name << " is copied." << std::endl;
}

// whoAmI
void DiamondTrap::whoAmI(void) {
    std::cout << "I am " << name << ", and my ClapTrap name is " << ClapTrap::name << std::endl;
}

// attack
void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target);
}

// Destructor
DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap " << name << " is destroyed." << std::endl;
}
