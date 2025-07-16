/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:54:04 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/10 18:26:40 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// Default constructor
ScalarConverter::ScalarConverter() {}

// Copy constructor
ScalarConverter::ScalarConverter(const ScalarConverter& other) {
    (void)other;
}

// Copy assignment operator
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}

// Destructor
ScalarConverter::~ScalarConverter() {}

static bool isCharLiteral(const std::string& str) {
    return str.length() == 3 && str[0] == '\'' && str[2] == '\'';
}

static bool isFloatPseudoLiteral(const std::string& str) {
    return str == "nanf" || str == "+inff" || str == "-inff";
}

static bool isDoublePseudoLiteral(const std::string& str) {
    return str == "nan" || str == "+inf" || str == "-inf";
}

static bool isFloatLiteral(const std::string& str) {
    return str.find('.') != std::string::npos && str[str.length() - 1] == 'f';
}

static bool isDoubleLiteral(const std::string& str) {
    return str.find('.') != std::string::npos && str[str.length() - 1] == 'f';
}

void ScalarConverter::convert(const std::string& literal) {
    char c;
    int i;
    float f;
    double d;

    std::cout << std::fixed << std::setprecision(1); 

    // CHAR
    if (isCharLiteral(literal)) {
        c = literal[1];
        i = static_cast<int>(c);
        f = static_cast<float>(c);
        d = static_cast<double>(c);
    }
    // FLOAT PSEUDO
    else if (isFloatPseudoLiteral(literal)) {
        c = 0;
        i = 0;
        f = std::strtof(literal.c_str(), NULL);
        d = static_cast<double>(f);
    }
    // DOUBLE PSEUDO
    else if (isDoublePseudoLiteral(literal)) {
        c = 0;
        i = 0;
        d = std::strtod(literal.c_str(), NULL);
        f = static_cast<float>(d);
    }
    // FLOAT
    else if (isFloatLiteral(literal)) {
        char* end;
        errno = 0;
        f = std::strtof(literal.c_str(), &end);
        if (errno == ERANGE) {
            std::cerr << "float: overflow/underflow\n";
            return;
        }
        d = static_cast<double>(f);
        i = static_cast<int>(f);
        c = static_cast<char>(f);
    }
    // DOUBLE
    else if (isDoubleLiteral(literal)) {
        char* end;
        errno = 0;
        d = std::strtod(literal.c_str(), &end);
        if (errno == ERANGE) {
            std::cerr << "double: overflow/underflow\n";
            return;
        }
        f = static_cast<float>(d);
        i = static_cast<int>(d);
        c = static_cast<char>(d);
    }
    // INT
    else {
        char* end;
        errno = 0;
        long val = std::strtol(literal.c_str(), &end, 10);
        if (*end != '\0' || errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            std::cerr << "int: invalid or out of range\n";
            return;
        }
        i = static_cast<int>(val);
        c = static_cast<char>(i);
        f = static_cast<float>(i);
        d = static_cast<double>(i);
    }

    // char
    std::cout << "char: ";
    if (isFloatPseudoLiteral(literal) || isDoublePseudoLiteral(literal) || std::isnan(d) || std::isinf(d))
        std::cout << "impossible" << std::endl;
    else if (std::isprint(c))
        std::cout << "'" << c << "'" << std::endl;
    else
        std::cout << "Non displayable" << std::endl;

    // int
    std::cout << "int: ";
    if (isFloatPseudoLiteral(literal) || isDoublePseudoLiteral(literal) || std::isnan(d) || std::isinf(d))
        std::cout << "impossible" << std::endl;
    else
        std::cout << i << std::endl;

    // float
    std::cout << "float: " << f << "f" << std::endl;

    // double
    std::cout << "double: " << d << std::endl;
}
