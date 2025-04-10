/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:21:08 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/10 16:45:08 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
    protected:
        std::string type;
    public:
    // Orthodox Canonical Form
    Animal();                                // Default constructor
    Animal(const Animal& other);           // Copy constructor
    Animal& operator=(const Animal& other); // Copy assignment
    virtual ~Animal();                               // Destructor
     
    // Member functions 
    virtual void makeSound() const;
    std::string getType() const;
};

#endif