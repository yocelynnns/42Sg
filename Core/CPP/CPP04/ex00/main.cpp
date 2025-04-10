/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:20:54 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/11 00:45:16 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    std::cout << "=== Correct Behavior with Virtual Functions ===" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << "Type of j: " << j->getType() << std::endl;
    std::cout << "Type of i: " << i->getType() << std::endl;

    i->makeSound(); // Should be Cat sound
    j->makeSound(); // Should be Dog sound
    meta->makeSound(); // Generic Animal sound

    delete meta;
    delete j;
    delete i;

    std::cout << "\n=== Wrong Behavior without Virtual Functions ===" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "Type of wrongCat: " << wrongCat->getType() << std::endl;

    wrongCat->makeSound(); // This will NOT call WrongCat's sound!
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;

    std::cout << "\n=== Copy Constructor & Assignment Operator Tests ===" << std::endl;

    // Cat Tests
    Cat originalCat;
    Cat copiedCat(originalCat);     // Copy constructor
    Cat assignedCat;
    assignedCat = originalCat;      // Assignment operator

    std::cout << "\n--- Cat Sounds ---\n";
    originalCat.makeSound();
    copiedCat.makeSound();
    assignedCat.makeSound();

    // Dog Tests
    Dog originalDog;
    Dog copiedDog(originalDog);     // Copy constructor
    Dog assignedDog;
    assignedDog = copiedDog;        // Assignment operator

    std::cout << "\n--- Dog Sounds ---\n";
    originalDog.makeSound();
    copiedDog.makeSound();
    assignedDog.makeSound();

    std::cout << "\n=== Polymorphism Check with Array of Animals ===\n" << std::endl;
    const int size = 4;
    Animal* animals[size];

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    for (int i = 0; i < size; i++) {
        std::cout << "Animal[" << i << "] (" << animals[i]->getType() << "): ";
        animals[i]->makeSound();
    }

    for (int i = 0; i < size; i++)
        delete animals[i];

    std::cout << "\n=== Object Slicing Test ===\n" << std::endl;
    Cat realCat;
    Animal slicedAnimal = realCat; // Slicing happens here

    std::cout << "Type of slicedAnimal: " << slicedAnimal.getType() << std::endl;
    slicedAnimal.makeSound(); // Will call Animal's sound, not Cat's

    std::cout << "\n=== Stacked Object Destruction Order ===\n" << std::endl;
    {
        Dog stackDog;
        Cat stackCat;
        // Destructor will be called automatically at scope exit
    }

    return 0;
}
