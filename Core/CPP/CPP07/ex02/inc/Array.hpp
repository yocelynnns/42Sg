/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:13:39 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/23 13:04:32 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept> 
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

template <typename Type>
class Array {
    private:
        Type* _array;
        unsigned int _size;
    public:
        Array();
        Array(unsigned int n);
        Array(const Array& other);
        Array& operator=(const Array& other);
        ~Array();

        Type& operator[](unsigned int index);
        const Type& operator[](unsigned int index) const;
        unsigned int size() const;
};

#include "../src/Array.tpp"

#endif
