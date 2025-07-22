/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:44:17 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/22 17:43:21 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <iostream> // for std::cout
// #include <cstdint> // for uintptr_t, but not possible bcs c++11

// either define manually or use unsigned long
#ifndef __UINTPTR_T_DEFINED
#define __UINTPTR_T_DEFINED
typedef unsigned long uintptr_t;
#endif

class Serializer {
    private:
        //  Orthodox Canonical Form
        Serializer();                                // Default constructor
        Serializer(const Serializer& other);           // Copy constructor
        Serializer& operator=(const Serializer& other); // Copy assignment
        ~Serializer();                               // Destructor
    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};

#endif
