/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:56:41 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/07/29 16:30:27 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <iostream>

class Span {
    private:
        unsigned int _maxSize;
        std::vector<int> _data;
    public:
        Span();
        Span(unsigned int n);
        Span(const Span& other);
        Span& operator=(const Span& other);
        ~Span();
        
        void addNumber(int n);  
        unsigned int shortestSpan() const;
        unsigned int longestSpan() const;

        template <typename InputIt>
        void addNumbers(InputIt begin, InputIt end) {
            unsigned int dist = static_cast<unsigned int>(std::distance(begin, end));
            if (_data.size() + dist > _maxSize)
                throw std::runtime_error("Adding range exceeds Span capacity");
            _data.insert(_data.end(), begin, end);
        }

        const std::vector<int>& getData() const;
};

#endif
