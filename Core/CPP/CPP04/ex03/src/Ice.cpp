/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:26 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 23:51:36 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {}
Ice::Ice(const Ice& other) : AMateria(other) {}
Ice& Ice::operator=(const Ice& other) {
    AMateria::operator=(other);
    return *this;
}
Ice::~Ice() {}

AMateria* Ice::clone() const {
    return new Ice(*this);
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
