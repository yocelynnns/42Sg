/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:25:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/10 15:31:38 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

// Default constructor
ScavTrap::ScavTrap() : ClapTrap("DefaultScav") {
    hitPts = 100;
    energyPts = 50;
    attackDmg = 20;
    maxHitPts = 100; 
    std::cout << "ScavTrap " << name << " is created (default)." << std::endl;
}

// Custom constructor
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    hitPts = 100;
    energyPts = 50;
    attackDmg = 20;
    maxHitPts = 100; 
    std::cout << "ScavTrap " << name << " is created." << std::endl;
}

// Copy constructor
ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    std::cout << "ScavTrap " << name << " is copied." << std::endl;
}

// Copy assignment operator
ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other); // call base class assignment
    }
    std::cout << "ScavTrap " << name << " is assigned." << std::endl;
    return *this;
}

// attack
void ScavTrap::attack(const std::string& target) {
    std::cout << "[ScavTrap] ";
    ClapTrap::attack(target);
}

// guardGate
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << name << " is now in Gate Keeper mode." << std::endl;
}

// Destructor
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << name << " is destroyed." << std::endl;
}
