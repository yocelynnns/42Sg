/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:53:07 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:22:51 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AMateria.hpp"

// Default constructor
AMateria::AMateria() : type("Unknown")
{
    std::cout << "AMateria " << type << " is created (default)." << std::endl;
}

// Custom constructor
AMateria::AMateria(std::string const & type) : type(type) 
{
    std::cout << "AMateria " << type << " is created." << std::endl;
}

// Copy constructor
AMateria::AMateria(const AMateria& other) : type(other.type)
{
    std::cout << "AMateria " << type << " is copied." << std::endl;
}

// Copy assignment operator
AMateria& AMateria::operator=(const AMateria& other)
{
    if (this != &other)
        type = other.type;
    std::cout << "AMateria " << type << " is assigned." << std::endl;
    return *this;
}

// Destructor
AMateria::~AMateria() {
    std::cout << "AMateria " << type << " is destroyed." << std::endl;
}

std::string const & AMateria::getType() const {
    return type;
}

void AMateria::use(ICharacter& target) {
    (void)target;
}
