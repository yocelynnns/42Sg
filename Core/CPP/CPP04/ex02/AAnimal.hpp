/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:21:08 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 16:20:37 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal {
    protected:
        std::string type;
    public:
        // Orthodox Canonical Form
        AAnimal();                                // Default constructor
        AAnimal(const AAnimal& other);           // Copy constructor
        AAnimal& operator=(const AAnimal& other); // Copy assignment
        virtual ~AAnimal();                               // Destructor
        
        // Member functions 
        virtual void makeSound() const = 0;
        std::string getType() const;
};

#endif