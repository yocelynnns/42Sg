/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:25:20 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:19:00 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Animal.hpp"

Animal::Animal() {
    type = "Animal";
    std::cout << "Animal Constructor called" << std::endl;
}

void Animal::makeSound() const {
    std::cout << "Animal makes some kind of noise..." << std::endl;
}

std::string Animal::getType() const {
    return type;
}

Animal::~Animal() {
    std::cout << "Animal Destructor called" << std::endl;
}

// Copy constructor
Animal::Animal(const Animal& other) : type(other.type)
{
    std::cout << "Animal is copied." << std::endl;
}

// Copy assignment operator
Animal& Animal::operator=(const Animal& other)
{
    if (this != &other)
        type = other.type;
    std::cout << "Animal is assigned." << std::endl;
    return *this;
}
