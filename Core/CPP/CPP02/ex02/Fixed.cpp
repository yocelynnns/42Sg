/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:51:10 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/27 15:55:34 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() {
    this->_fixedValue = 0;
}

Fixed::Fixed(const Fixed& copy) {
    *this = copy;
}

Fixed &Fixed::operator=(const Fixed &copy) {
    if (this != &copy)
        this->_fixedValue = copy._fixedValue;
    return *this;
}

Fixed::~Fixed() { }

Fixed::Fixed (const int num) {
    this->_fixedValue = num << this->_fractBits;
}

Fixed::Fixed (const float num) {
    this->_fixedValue = roundf(num * (1 << this->_fractBits));
}

float Fixed::toFloat( void ) const {
    return (float)this->_fixedValue / (1 << this->_fractBits);
}

int Fixed::toInt( void ) const {
    return this->_fixedValue >> this->_fractBits;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
}

bool Fixed::operator>(const Fixed &copy) const {
    return this->_fixedValue > copy._fixedValue;
}

bool Fixed::operator<(const Fixed &copy) const {
    return this->_fixedValue < copy._fixedValue;
}

bool Fixed::operator>=(const Fixed &copy) const {
    return this->_fixedValue >= copy._fixedValue;
}

bool Fixed::operator<=(const Fixed &copy) const {
    return this->_fixedValue <= copy._fixedValue;
}

bool Fixed::operator==(const Fixed &copy) const {
    return this->_fixedValue == copy._fixedValue;
}

bool Fixed::operator!=(const Fixed &copy) const {
    return this->_fixedValue != copy._fixedValue;
}

Fixed Fixed::operator+(const Fixed &copy) const {
    return Fixed(toFloat() + copy.toFloat());
}

Fixed Fixed::operator-(const Fixed &copy) const {
    return Fixed(toFloat() - copy.toFloat());
}

Fixed Fixed::operator*(const Fixed &copy) const {
    return Fixed(toFloat() * copy.toFloat());
}

Fixed Fixed::operator/(const Fixed &copy) const
{
    if (copy._fixedValue == 0)
    {
        std::cerr << "Error: Division by zero!" << std::endl;
        return Fixed(0);
    }
    return Fixed(toFloat() / copy.toFloat());
}

Fixed Fixed::operator++(int) {
    Fixed temp = *this; // Store old value
    this->_fixedValue++;
    return temp;
}

Fixed &Fixed::operator++() {
    this->_fixedValue++;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp = *this;
    this->_fixedValue--;
    return temp;
}

Fixed &Fixed::operator--() {
    this->_fixedValue--;
    return *this;
}

Fixed Fixed::max(const Fixed &a, const Fixed &b)
{
    if (a > b)
        return a;
    else
        return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    if (a > b)
        return a;
    else
        return b;
}

Fixed Fixed::min(const Fixed &a, const Fixed &b)
{
    if (a < b)
        return a;
    else
        return b;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    if (a < b)
        return a;
    else
        return b;
}