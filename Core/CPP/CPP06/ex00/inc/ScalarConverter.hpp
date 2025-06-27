/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:20:25 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/02 21:13:45 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include <sstream>

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