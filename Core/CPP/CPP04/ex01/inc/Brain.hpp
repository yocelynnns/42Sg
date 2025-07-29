/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:14:13 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 01:20:24 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <iostream>

class Brain
{
    public:
        std::string ideas[100];
        // Orthodox Canonical Form
        Brain();                                // Default constructor
        Brain(const Brain& other);           // Copy constructor
        Brain& operator=(const Brain& other); // Copy assignment
        virtual ~Brain();                               // Destructor
};

#endif