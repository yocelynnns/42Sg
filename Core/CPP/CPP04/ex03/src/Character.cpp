/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:15 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/14 16:29:48 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Character.hpp"

Character::Character() : name("Unnamed") {
    for (int i = 0; i < 4; ++i)
        inventory[i] = NULL;
    std::cout << "Character " << name << " is created (default)." << std::endl;
}

Character::Character(std::string const & name) : name(name) {
    for (int i = 0; i < 4; ++i)
        inventory[i] = NULL;
    std::cout << "Character " << name << " is created." << std::endl;
}

Character::Character(const Character& other) : name(other.name) {
    for (int i = 0; i < 4; ++i) {
        if (other.inventory[i])
            inventory[i] = other.inventory[i]->clone();
        else
            inventory[i] = NULL;
    }
    std::cout << "Character " << name << " is copied." << std::endl;
}

Character& Character::operator=(const Character& other) {
    if (this != &other)
    {
        name = other.name;
        for (int i = 0; i < 4; ++i)
        {
            delete inventory[i];
            if (other.inventory[i])
                inventory[i] = other.inventory[i]->clone();
            else
                inventory[i] = NULL;
        }
    }
    std::cout << "Character " << name << " is assigned." << std::endl;
    return *this;
}

Character::~Character() {
    for (int i = 0; i < 4; ++i)
        delete inventory[i];
    std::cout << "Character " << name << " is destroyed." << std::endl;
}

std::string const & Character::getName() const {
    return name;
}

void Character::equip(AMateria* m) {
    if (!m)
        return;
    for (int i = 0; i < 4; ++i)
    {
        if (!inventory[i])
        {
            inventory[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx) {
    if (idx >= 0 && idx < 4)
    {
        delete inventory[idx];
        inventory[idx] = NULL;
    }
}

void Character::use(int idx, ICharacter& target) {
    if (idx >= 0 && idx < 4 && inventory[idx])
        inventory[idx]->use(target);
}
