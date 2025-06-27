/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:10:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/24 14:08:54 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class BigInt {
private:
    std::string value;

    void strip_leading_zeros();

public:
    BigInt();
    BigInt(const std::string& s);
    BigInt(const BigInt& other);
    BigInt& operator=(const BigInt& other);
    ~BigInt();

    BigInt operator+(const BigInt& rhs) const;
    BigInt& operator+=(const BigInt& rhs);

    BigInt operator<<(int n) const; // shift left (multiply by 10^n)
    BigInt operator>>(int n) const; // shift right (divide by 10^n)

    BigInt operator++(int);
    BigInt& operator++();

    bool operator==(const BigInt& rhs) const;
    bool operator!=(const BigInt& rhs) const;
    bool operator<(const BigInt& rhs) const;
    bool operator>(const BigInt& rhs) const;

    std::string to_string() const;
};

std::ostream& operator<<(std::ostream& os, const BigInt& b);

#endif
