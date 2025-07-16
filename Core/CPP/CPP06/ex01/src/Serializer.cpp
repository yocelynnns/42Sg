/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:58:51 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/10 18:26:07 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}

// Default constructor
Serializer::Serializer() {}

// Copy constructor
Serializer::Serializer(const Serializer& other) {
    (void)other;
}

// Copy assignment operator
Serializer& Serializer::operator=(const Serializer& other) {
    (void)other;
    return *this;
}

// Destructor
Serializer::~Serializer() {}