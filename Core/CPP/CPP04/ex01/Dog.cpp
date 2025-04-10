/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:29:50 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 01:37:15 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
    type = "Dog";
    brain = new Brain();
    std::cout << "Dog Constructor called" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "woof! woof!" << std::endl;
}

Dog::~Dog() {
    delete brain;
    std::cout << "Dog Destructor called" << std::endl;
}

// Copy constructor
Dog::Dog(const Dog& other) : Animal(other) {
    brain = new Brain(*other.brain);
    std::cout << "Dog is copied." << std::endl;
}

// Copy assignment operator
Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {
        Animal::operator=(other);
        delete brain;
        brain = new Brain(*other.brain); // deep copy
    }
    std::cout << "Dog is assigned." << std::endl;
    return *this;
}

Brain* Dog::getBrain() const {
    return brain;
}