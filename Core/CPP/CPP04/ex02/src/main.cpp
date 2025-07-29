/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:20:54 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 18:20:29 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AAnimal.hpp"
#include "../inc/Dog.hpp"
#include "../inc/Cat.hpp"

int main() {
    std::cout << "=== Basic Instantiation ===" << std::endl;
    Cat cat;
    Dog dog;

    std::cout << "\n=== Polymorphism Test ===" << std::endl;
    AAnimal* animals[2];
    animals[0] = new Cat();
    animals[1] = new Dog();

    for (int i = 0; i < 2; ++i) {
        std::cout << animals[i]->getType() << " makes sound: ";
        animals[i]->makeSound();
    }

    std::cout << "\n=== Destructor Cleanup ===" << std::endl;
    for (int i = 0; i < 2; ++i) {
        delete animals[i];
    }

    std::cout << "\n=== Copy Constructor Test ===" << std::endl;
    Cat originalCat;
    Cat copiedCat(originalCat);

    Dog originalDog;
    Dog copiedDog(originalDog);

    std::cout << "\n=== Assignment Operator Test ===" << std::endl;
    Cat assignedCat;
    assignedCat = cat;

    Dog assignedDog;
    assignedDog = dog;

    std::cout << "\n=== Abstract Base Class Test (Compilation should fail if uncommented) ===" << std::endl;
    // AAnimal testAnimal; // ❌ Uncommenting this line should cause a compiler error (abstract class)

    return 0;
}