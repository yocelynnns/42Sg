/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:09:31 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/26 14:40:58 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp" 

Vec2::~Vec2() {
    
}

Vec2::Vec2() {
    data[0] = 0;
    data[1] = 0;
}

Vec2::Vec2(int x, int y)
{
    data[0] = x;
    data[1] = y;
}

Vec2::Vec2(const Vec2& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
}

Vec2& Vec2::operator=(const Vec2& other) {
    if (this != &other) {
        data[0] = other.data[0];
        data[1] = other.data[1];
    }
    return *this;
}

int& Vec2::operator[](size_t index) {
    if (index >= 2) {
        std::cerr << "Index " << index << " out of range\n";
        std::exit(EXIT_FAILURE);
    }
    return data[index];
}

const int& Vec2::operator[](size_t index) const {
    if (index >= 2) {
        std::cerr << "Index " << index << " out of range\n";
        std::exit(EXIT_FAILURE);
    }
    return data[index];
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(data[0] + rhs.data[0], data[1] + rhs.data[1]);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(data[0] - rhs.data[0], data[1] - rhs.data[1]);
}

Vec2 Vec2::operator*(int scalar) const {
    return Vec2(data[0] * scalar, data[1] * scalar);
}

Vec2 Vec2::operator/(int scalar) const {
    if (scalar == 0)
    {
        std::cerr << "Error: division by 0!\n";
        return Vec2(0,0);
    }
    return Vec2(data[0] / scalar, data[1] / scalar);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    data[0] += rhs.data[0];
    data[1] += rhs.data[1];
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    data[0] -= rhs.data[0];
    data[1] -= rhs.data[1];
    return *this;
}

Vec2& Vec2::operator*=(int scalar) {
    data[0] *= scalar;
    data[1] *= scalar;
    return *this;
}

bool Vec2::operator==(const Vec2& rhs) const {
    return data[0] == rhs.data[0] && data[1] == rhs.data[1];
}

bool Vec2::operator!=(const Vec2& rhs) const {
    return !(*this == rhs);
}

Vec2 Vec2::operator++(int) {
    Vec2 temp = *this;
    ++(*this);
    return temp;
}

Vec2& Vec2::operator++() {
    ++data[0];
    ++data[1];
    return *this;
}

Vec2 Vec2::operator--(int) {
    Vec2 temp = *this;
    --(*this);
    return temp;
}

Vec2& Vec2::operator--() {
    --data[0];
    --data[1];
    return *this;
}

int Vec2::getX() const {
    return data[0];
}

int Vec2::getY() const {
    return data[1];
}

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "{" << v.getX() << "," << v.getY() << "}";
    return os;
}

Vec2 operator*(int scalar, const Vec2& v) {
    return v * scalar;
}

Vec2 operator-(const Vec2& rhs) {
    return rhs * -1;
}