/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:38:43 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/11 17:15:24 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename Type>
Array<Type>::Array()
{
    _array = NULL;
    _size = 0;
}

template <typename Type>
Array<Type>::Array(unsigned int n)
{
    _array = new Type[n];
    _size = n;
}

template <typename Type>
Array<Type>::Array(const Array<Type>& other)
{
    _size = other._size;
    _array = new Type[_size];
    
    unsigned int i = 0;
    while (i < _size)
    {
        _array[i] = other._array[i];
        ++i;
    }
}

template <typename Type>
Array<Type>& Array<Type>::operator=(const Array<Type>& other)
{
    if (this != &other)
    {
        delete[] _array;
        _size = other._size;
        _array = new Type[_size];
        
        unsigned int i = 0;
        while (i < _size)
        {
            _array[i] = other._array[i];
            ++i;
        }
    }
    return *this;
}

template <typename Type>
Array<Type>::~Array() {
    delete[] _array;
}

template <typename Type>
Type& Array<Type>::operator[](unsigned int index)
{
    if (index >= _size)
        throw std::out_of_range("Index out of bounds!");
    return _array[index];
}

template <typename Type>
const Type& Array<Type>::operator[](unsigned int index) const
{
    if (index >= _size)
        throw std::out_of_range("Index out of bounds!");
    return _array[index];
}

template <typename Type>
unsigned int Array<Type>::size() const {
    return _size;
}
