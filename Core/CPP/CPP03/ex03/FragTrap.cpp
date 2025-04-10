/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:51:35 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/10 15:37:36 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

// Default constructor
FragTrap::FragTrap() : ClapTrap("DefaultFrag") {
    hitPts = 100;
    energyPts = 100;
    attackDmg = 30;
    maxHitPts = 100;
    std::cout << "FragTrap " << name << " is created (default)." << std::endl;
}

// Custom constructor
FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    hitPts = 100;
    energyPts = 100;
    attackDmg = 30;
    maxHitPts = 100;
    std::cout << "FragTrap " << name << " is created." << std::endl;
}

// Copy constructor
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    std::cout << "FragTrap " << name << " is copied." << std::endl;
}

// Copy assignment operator
FragTrap& FragTrap::operator=(const FragTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other); // call base class assignment
    }
    std::cout << "FragTrap " << name << " is assigned." << std::endl;
    return *this;
}

// highFiveGuys
void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << name << " requested a high five." << std::endl;
}

// Destructor
FragTrap::~FragTrap() {
    std::cout << "FragTrap " << name << " is destroyed." << std::endl;
}
