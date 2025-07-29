/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:43:50 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/25 15:33:35 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() {
    _maxSize = 0;
}

Span::Span(unsigned int n) {
    _maxSize = n;
}

Span::Span(const Span& other) {
    *this = other;
}

Span& Span::operator=(const Span& other) {
    if (this != &other)   
    {
        _maxSize = other._maxSize;
        _data = other._data;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int n) {
    if (_data.size() >= _maxSize)
        throw std::runtime_error("Cannot add more numbers, span is full.");
    _data.push_back(n);
}

unsigned int Span::shortestSpan() const {
    if (_data.size() < 2)
        throw std::runtime_error("Not enough numbers to find span.");
    std::vector<int> sorted = _data;
    std::sort(sorted.begin(), sorted.end());

    unsigned int minSpan = sorted[1] - sorted[0];
    for (size_t i = 1; i < sorted.size() - 1; ++i) {
        unsigned int span = sorted[i + 1] - sorted[i];
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}

unsigned int Span::longestSpan() const {
    if (_data.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span.");

    int minVal = *std::min_element(_data.begin(), _data.end());
    int maxVal = *std::max_element(_data.begin(), _data.end());

    return maxVal - minVal;
}

const std::vector<int>& Span::getData() const {
    return _data;
}
