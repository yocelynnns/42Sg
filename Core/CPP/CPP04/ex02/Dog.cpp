/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:29:50 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 15:39:14 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
    type = "Dog";
    std::cout << "Dog Constructor called" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "woof! woof!" << std::endl;
}

Dog::~Dog() {
    std::cout << "Dog Destructor called" << std::endl;
}

// Copy constructor
Dog::Dog(const Dog& other) : AAnimal(other) {
    std::cout << "Dog is copied." << std::endl;
}

// Copy assignment operator
Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {
        AAnimal::operator=(other);
    }
    std::cout << "Dog is assigned." << std::endl;
    return *this;
}
