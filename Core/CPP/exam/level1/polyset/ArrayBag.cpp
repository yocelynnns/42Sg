/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArrayBag.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:39:17 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 20:50:19 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArrayBag.hpp"
#include <iostream>

ArrayBag::ArrayBag() : capacity(10), count(0) {
    data = new int[capacity];
}

ArrayBag::ArrayBag(const ArrayBag& other) {
    copyFrom(other);
}

ArrayBag& ArrayBag::operator=(const ArrayBag& other) {
    if (this != &other) {
        delete[] data;
        copyFrom(other);
    }
    return *this;
}

void ArrayBag::copyFrom(const ArrayBag& other) {
    capacity = other.capacity;
    count = other.count;
    data = new int[capacity];
    int i = 0;
    while (i < count)
    {
        data[i] = other.data[i];
        ++i;
    }
}

ArrayBag::~ArrayBag() {
    delete[] data;
}

void ArrayBag::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    int i = 0;
    while (i < count)
    {
        newData[i] = data[i];
        ++i;
    }
    delete[] data;
    data = newData;
}

void ArrayBag::insert(int value) {
    if (count == capacity)
        resize();
    data[count++] = value;
}

int ArrayBag::size() const {
    return count;
}

void ArrayBag::print() const
{
    std::cout << "ArrayBag: ";
    int i = 0;
    while (i < count)
    {
        std::cout << data[i] << " ";
        ++i;
    }
    std::cout << std::endl;
}

bool ArrayBag::has(int value) const
{
    int i = 0;
    while (i < count)
    {
        if (data[i] == value)
            return true;
        ++i;
    }
    return false;
}
