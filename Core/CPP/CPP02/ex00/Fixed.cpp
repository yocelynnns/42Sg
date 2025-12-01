/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:46:16 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/27 15:28:23 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() {
    std::cout << "Default constructor called" << std::endl;
    this->_fixedValue = 0;
}

Fixed::Fixed(const Fixed& copy) {
    std::cout << "Copy constructor called" << std::endl;
    *this = copy;
}

Fixed &Fixed::operator=(const Fixed& copy) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &copy)
        this->_fixedValue = copy.getRawBits();
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits( void ) const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->_fixedValue;
}

void Fixed::setRawBits( int const raw ) {
    this->_fixedValue = raw;
}