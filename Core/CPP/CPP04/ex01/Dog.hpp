/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:22:44 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 01:37:04 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
    private:
        Brain* brain;
    public:
        // Orthodox Canonical Form
        Dog();                                // Default constructor
        Dog(const Dog& other);           // Copy constructor
        Dog& operator=(const Dog& other); // Copy assignment
        ~Dog();   
        
        // Member Functions
        void makeSound() const;
        Brain* getBrain() const;
};

#endif