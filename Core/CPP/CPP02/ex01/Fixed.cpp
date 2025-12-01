/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:43:49 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/25 20:49:05 by ysetiawa         ###   ########.fr       */
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

Fixed &Fixed::operator=(const Fixed &copy) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &copy)
        this->_fixedValue = copy._fixedValue;
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed (const int num) {
    std::cout << "Int constructor called" << std::endl;
    this->_fixedValue = num << _fractBits;
}

Fixed::Fixed (const float num) {
    std::cout << "Float constructor called" << std::endl;
    this->_fixedValue = roundf(num * (1 << _fractBits));
}

float Fixed::toFloat( void ) const {
    return (float)this->_fixedValue / (1 << _fractBits);
}

int Fixed::toInt( void ) const {
    return this->_fixedValue >> _fractBits;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
}