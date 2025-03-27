/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:51:08 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/26 19:11:51 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>

class Fixed
{
    private:
        int _fixedValue;
        static const int _fractBits = 8;

    public:
        Fixed();
        Fixed (const int num);
        Fixed (const float num);
        Fixed(const Fixed& copy);
        Fixed &operator=(const Fixed &copy);
        ~Fixed();

        int getRawBits( void ) const;
        void setRawBits( int const raw );
        float toFloat( void ) const;
        int toInt( void ) const;
        
        bool operator>(const Fixed &copy) const;
        bool operator<(const Fixed &copy) const;
        bool operator>=(const Fixed &copy) const;
        bool operator<=(const Fixed &copy) const;
        bool operator==(const Fixed &copy) const;
        bool operator!=(const Fixed &copy) const;
        
        Fixed operator+(const Fixed &copy) const;
        Fixed operator-(const Fixed &copy) const;
        Fixed operator*(const Fixed &copy) const;
        Fixed operator/(const Fixed &copy) const;
        
        Fixed operator++(int);
        Fixed &operator++();
        Fixed operator--(int);
        Fixed &operator--();

        static Fixed max(const Fixed &a, const Fixed &b);
        static Fixed &max(Fixed &a, Fixed &b);
        static Fixed min(const Fixed &a, const Fixed &b);
        static Fixed &min(Fixed &a, Fixed &b);
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif