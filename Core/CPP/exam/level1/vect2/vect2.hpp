/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:10:16 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/26 14:40:37 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <string>
#include <cstdlib>

class Vec2 {
private:
    int data[2];

public:
    Vec2();
    Vec2(int x, int y);
    Vec2(const Vec2& other);
    Vec2& operator=(const Vec2& other);
    ~Vec2();

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(int scalar) const;
    Vec2 operator/(int scalar) const;

    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator*=(int scalar);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator++(int);
    Vec2& operator++();   
    Vec2 operator--(int);
    Vec2& operator--();

    int getX() const;
    int getY() const;
};

std::ostream& operator<<(std::ostream& os, const Vec2& v);
Vec2 operator*(int scalar, const Vec2& v);
Vec2 operator-(const Vec2& rhs);

#endif