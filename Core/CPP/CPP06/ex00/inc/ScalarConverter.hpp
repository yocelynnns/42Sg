/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:20:25 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/22 15:48:27 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream> // for std::cout
#include <cmath>  // for isnan, isinf
#include <iomanip> // for std::setprecision
#include <cstdlib>  // for strtof, strtod
#include <cctype> // for std::isprint
#include <cerrno> // for errno
#include <climits>  // for INT_MAX, INT_MIN

class ScalarConverter {
    private:
        //  Orthodox Canonical Form
        ScalarConverter();                                // Default constructor
        ScalarConverter(const ScalarConverter& other);           // Copy constructor
        ScalarConverter& operator=(const ScalarConverter& other); // Copy assignment
        ~ScalarConverter();                               // Destructor
    public:
        static void convert(const std::string& literal);
};

#endif
