/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:41:17 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:17:28 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cat.hpp"

Cat::Cat() {
    type = "Cat";
    brain = new Brain();
    std::cout << "Cat Constructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "meow! meow!" << std::endl;
}

Cat::~Cat() {
    delete brain;
    std::cout << "Cat Destructor called" << std::endl;
}

// Copy constructor
Cat::Cat(const Cat& other) : Animal(other) {
    brain = new Brain(*other.brain);
    std::cout << "Cat is copied." << std::endl;
}

// Copy assignment operator
Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        Animal::operator=(other);
        delete brain;
        brain = new Brain(*other.brain); // deep copy
    }
    std::cout << "Cat is assigned." << std::endl;
    return *this;
}

Brain* Cat::getBrain() const {
    return brain;
}
