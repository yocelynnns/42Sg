/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:41:29 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 00:32:36 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {
    public:
        // Orthodox Canonical Form
        Cat();                                // Default constructor
        Cat(const Cat& other);           // Copy constructor
        Cat& operator=(const Cat& other); // Copy assignment
        ~Cat();   
        
        // Member Functions
        void makeSound() const;
};

#endif