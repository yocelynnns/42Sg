/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:15:19 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:18:05 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {
    type = "WrongAnimal";
    std::cout << "WrongAnimal Constructor called" << std::endl;
}

void WrongAnimal::makeSound() const {
    std::cout << "WrongAnimal makes a generic wrong sound..." << std::endl;
}

std::string WrongAnimal::getType() const {
    return type;
}

WrongAnimal::~WrongAnimal() {
    std::cout << "WrongAnimal Destructor called" << std::endl;
}

// Copy constructor
WrongAnimal::WrongAnimal(const WrongAnimal& other) : type(other.type)
{
    std::cout << "WrongAnimal is copied." << std::endl;
}

// Copy assignment operator
WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
    if (this != &other)
        type = other.type;
    std::cout << "WrongAnimal is assigned." << std::endl;
    return *this;
}

