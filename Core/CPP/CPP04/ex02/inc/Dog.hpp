/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:22:44 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:20:41 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "AAnimal.hpp"

class Dog : public AAnimal {
    public:
        // Orthodox Canonical Form
        Dog();                                // Default constructor
        Dog(const Dog& other);           // Copy constructor
        Dog& operator=(const Dog& other); // Copy assignment
        ~Dog();   
        
        // Member Functions
        void makeSound() const;
};

#endif