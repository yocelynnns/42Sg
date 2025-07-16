/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArrayBag.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:39:17 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/02 14:46:06 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArrayBag.hpp"

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
    for (int i = 0; i < count; ++i)
        data[i] = other.data[i];
}

ArrayBag::~ArrayBag() {
    delete[] data;
}

void ArrayBag::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (int i = 0; i < count; ++i)
        newData[i] = data[i];
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

void ArrayBag::print() const {
    std::cout << "ArrayBag: ";
    for (int i = 0; i < count; ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

bool ArrayBag::has(int value) const {
    for (int i = 0; i < count; ++i) {
        if (data[i] == value)
            return true;
    }
    return false;
}
