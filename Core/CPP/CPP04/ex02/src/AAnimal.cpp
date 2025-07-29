/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:25:20 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:19:52 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AAnimal.hpp"

AAnimal::AAnimal() {
    type = "AAnimal";
    std::cout << "AAnimal Constructor called" << std::endl;
}

std::string AAnimal::getType() const {
    return type;
}

AAnimal::~AAnimal() {
    std::cout << "AAnimal Destructor called" << std::endl;
}

// Copy constructor
AAnimal::AAnimal(const AAnimal& other) : type(other.type)
{
    std::cout << "AAnimal is copied." << std::endl;
}

// Copy assignment operator
AAnimal& AAnimal::operator=(const AAnimal& other)
{
    if (this != &other)
        type = other.type;
    std::cout << "AAnimal is assigned." << std::endl;
    return *this;
}
