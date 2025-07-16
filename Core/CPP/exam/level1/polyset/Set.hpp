/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:40:02 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/02 14:46:41 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "SearchableBag.hpp"
#include "ArrayBag.hpp"
#include "TreeBag.hpp"
#include <typeinfo>

class Set : public SearchableBag {
private:
    SearchableBag* bag;

public:
    Set(SearchableBag* b);
    Set(const Set& other);
    Set& operator=(const Set& other);
    ~Set();

    void insert(int value);
    int size() const;
    void print() const;
    bool has(int value) const;
};

#endif
