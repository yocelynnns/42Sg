/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:09:31 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 21:13:10 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

BigInt::~BigInt() {
    
}

BigInt::BigInt() : value("0") {
    
}

BigInt::BigInt(const std::string& s) {
    size_t i = 0;
    while (i < s.length() && s[i] == '0') {
        ++i;
    }
    
    if (i == s.length()) {
        value = "0";
    } else {
        value = s.substr(i);
    }
}

BigInt::BigInt(const BigInt& other) : value(other.value) {}

BigInt& BigInt::operator=(const BigInt& other) {
    value = other.value;
    return *this;
}

void BigInt::strip_leading_zeros() {
    size_t i = 0;
    while (i < value.length() - 1 && value[i] == '0')
        ++i;
    value = value.substr(i);
}

BigInt BigInt::operator+(const BigInt& rhs) const {
    std::string a = value;
    std::string b = rhs.value;
    std::string result = "";

    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digitA, digitB;

        if (i >= 0) {
            digitA = a[i] - '0';
            i--;
        } else {
            digitA = 0;
        }

        if (j >= 0) {
            digitB = b[j] - '0';
            j--;
        } else {
            digitB = 0;
        }

        int sum = digitA + digitB + carry;
        carry = sum / 10;
        result = char(sum % 10 + '0') + result;
    }

    return BigInt(result);
}

BigInt& BigInt::operator+=(const BigInt& rhs) {
    *this = *this + rhs;
    return *this;
}

BigInt BigInt::operator<<(int n) const {
    if (value == "0")
        return *this;
    return BigInt(value + std::string(n, '0'));
}

BigInt BigInt::operator>>(int n) const {
    if (value.length() <= (size_t)n)
        return BigInt("0");
    return BigInt(value.substr(0, value.length() - n));
}

BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    *this += BigInt("1");
    return temp;
}

BigInt& BigInt::operator++() {
    *this += BigInt("1");
    return *this;
}

bool BigInt::operator==(const BigInt& rhs) const {
    return value == rhs.value;
}

bool BigInt::operator!=(const BigInt& rhs) const {
    return value != rhs.value;
}

bool BigInt::operator<(const BigInt& rhs) const {
    if (value.length() != rhs.value.length())
        return value.length() < rhs.value.length();
    return value < rhs.value;
}

bool BigInt::operator>(const BigInt& rhs) const {
    return rhs < *this;
}

std::string BigInt::to_string() const {
    return value;
}

std::ostream& operator<<(std::ostream& os, const BigInt& b) {
    os << b.to_string();
    return os;
}
