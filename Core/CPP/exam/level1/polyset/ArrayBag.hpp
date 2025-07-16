/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArrayBag.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:39:02 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/02 14:46:17 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYBAG_HPP
#define ARRAYBAG_HPP

#include "SearchableBag.hpp"
#include <iostream>

class ArrayBag : public SearchableBag {
private:
    int* data;
    int capacity;
    int count;

    void resize();
    void copyFrom(const ArrayBag& other);

public:
    ArrayBag();
    ArrayBag(const ArrayBag& other);
    ArrayBag& operator=(const ArrayBag& other);
    ~ArrayBag();

    void insert(int value);
    int size() const;
    void print() const;
    bool has(int value) const;
};

#endif
