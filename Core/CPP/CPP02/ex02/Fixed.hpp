/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:51:08 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/25 20:52:53 by ysetiawa         ###   ########.fr       */
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
        Fixed(const Fixed& copy);
        Fixed &operator = (const Fixed &copy);
        ~Fixed();
        int getRawBits( void ) const;
        void setRawBits( int const raw );
};

#endif