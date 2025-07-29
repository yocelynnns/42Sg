/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:21 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/14 16:25:24 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cure.hpp"

Cure::Cure() : AMateria("cure")
{
    std::cout << "[Cure] " << type << " is created (default)." << std::endl;
}

Cure::Cure(const Cure& other) : AMateria(other)
{
    std::cout << "[Cure] " << type << " is copied." << std::endl;
}

Cure& Cure::operator=(const Cure& other)
{
    AMateria::operator=(other);
    std::cout << "Cure " << type << " is assigned." << std::endl;
    return *this;
}

Cure::~Cure() {
    std::cout << "Cure " << type << " is destroyed." << std::endl;
}

AMateria* Cure::clone() const {
    return new Cure(*this);
}

void Cure::use(ICharacter& target) {
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
