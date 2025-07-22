/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:58:51 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/22 18:16:32 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

// <reinterpret_cast>
// reinterprets the binary representation of one type as another
// usually for pointer or integer conversions

// Turning a pointer into an integer 
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

// Turning an integer back into a pointer
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
Serializer::~Serializer() {
    
}
