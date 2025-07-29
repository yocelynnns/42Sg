/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:26 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/14 15:35:02 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Ice.hpp"

Ice::Ice() : AMateria("ice")
{
    std::cout << "[Ice] " << type << " is created (default)." << std::endl;
}

Ice::Ice(const Ice& other) : AMateria(other)
{
    std::cout << "[Ice] " << type << " is copied." << std::endl;
}

Ice& Ice::operator=(const Ice& other) {
    AMateria::operator=(other);
    std::cout << "Ice " << type << " is assigned." << std::endl;
    return *this;
}
Ice::~Ice() {
    std::cout << "Ice " << type << " is destroyed." << std::endl;
}

AMateria* Ice::clone() const {
    return new Ice(*this);
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
