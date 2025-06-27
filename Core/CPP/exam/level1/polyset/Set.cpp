/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:40:11 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 20:43:36 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Set.hpp"
#include "ArrayBag.hpp"
#include "TreeBag.hpp"
#include <typeinfo>

Set::Set(SearchableBag* b) : bag(b) {}

Set::~Set() {
    delete bag;
}

Set::Set(const Set& other) {
    if (typeid(*other.bag) == typeid(ArrayBag)) {
        bag = new ArrayBag(*static_cast<ArrayBag*>(other.bag));
    } else if (typeid(*other.bag) == typeid(TreeBag)) {
        bag = new TreeBag(*static_cast<TreeBag*>(other.bag));
    } else {
        bag = 0;
    }
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        delete bag;
        if (typeid(*other.bag) == typeid(ArrayBag)) {
            bag = new ArrayBag(*static_cast<ArrayBag*>(other.bag));
        } else if (typeid(*other.bag) == typeid(TreeBag)) {
            bag = new TreeBag(*static_cast<TreeBag*>(other.bag));
        } else {
            bag = 0;
        }
    }
    return *this;
}

void Set::insert(int value) {
    bag->insert(value);
}

int Set::size() const {
    return bag->size();
}

void Set::print() const {
    bag->print();
}

bool Set::has(int value) const {
    return bag->has(value);
}
