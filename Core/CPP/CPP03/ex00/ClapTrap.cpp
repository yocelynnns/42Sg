/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:45:48 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 17:38:58 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

// Default constructor
ClapTrap::ClapTrap()
    : name("Unnamed"), hitPts(10), energyPts(10), attackDmg(0)
{
    std::cout << "ClapTrap " << name << " is created (default)." << std::endl;
}

// Custom constructor
ClapTrap::ClapTrap(std::string name)
    : name(name), hitPts(10), energyPts(10), attackDmg(0)
{
    std::cout << "ClapTrap " << name << " is created." << std::endl;
}

// Copy constructor
ClapTrap::ClapTrap(const ClapTrap& other)
    : name(other.name), hitPts(other.hitPts), energyPts(other.energyPts), attackDmg(other.attackDmg)
{
    std::cout << "ClapTrap " << name << " is copied." << std::endl;
}

// Copy assignment operator
ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
    if (this != &other)
    {
        name = other.name;
        hitPts = other.hitPts;
        energyPts = other.energyPts;
        attackDmg = other.attackDmg;
    }
    std::cout << "ClapTrap " << name << " is assigned." << std::endl;
    return *this;
}

// attack
void ClapTrap::attack(const std::string& target)
{
    if (hitPts < 1) {
        std::cout << "ClapTrap " << name << " is dead and cannot attack." << std::endl;
        return ;
    }
    if (energyPts < 1) {
        std::cout << "ClapTrap " << name << " does not have enough energy to attack." << std::endl;
        return ;
    }
    std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attackDmg << " points of damage!" << std::endl;
    int oldEnergy = energyPts;
    energyPts -= 1;
    std::cout << "ENERGYY------- Before: " << oldEnergy << " After: " << energyPts << std::endl;
}

// takeDamage
void ClapTrap::takeDamage(unsigned int amount)
{
    if (hitPts < 1) {
        std::cout << "ClapTrap " << name << " is already dead." << std::endl;
        return ;
    }
    int oldHP = hitPts;
    std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!" << std::endl;
    hitPts -= (int)amount;
    if (hitPts <= 0)
    {
        hitPts = 0;
        std::cout << "ClapTrap " << name << " has died." << std::endl;
        std::cout << "HP--------- Before: " << oldHP << " After: " << hitPts << std::endl;
        return ;
    }
    std::cout << "HP--------- Before: " << oldHP << " After: " << hitPts << std::endl;
}

// beRepaired
void ClapTrap::beRepaired(unsigned int amount)
{
    if (hitPts < 1) {
        std::cout << "ClapTrap " << name << " is dead and cannot be repaired." << std::endl;
        return ;
    }
    if (energyPts < 1) {
        std::cout << "ClapTrap " << name << " does not have enough energy to be repaired." << std::endl;
        return ;
    }
    int oldHP = hitPts;
    hitPts += (int)amount;
    if (hitPts > 10)
        hitPts = 10;
    std::cout << "ClapTrap " << name << " is repaired: " << oldHP << " -> " << hitPts << " HP." << std::endl;
    int oldEnergy = energyPts;
    energyPts -= 1;
    std::cout << "ENERGYY------- Before: " << oldEnergy << " After: " << energyPts << std::endl;
}

// Destructor
ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << this->name << " is destroyed." << std::endl;
}