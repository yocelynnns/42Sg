/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 23:20:54 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/14 13:54:14 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Animal.hpp"
#include "../inc/Dog.hpp"
#include "../inc/Cat.hpp"
#include "../inc/Brain.hpp"

int main() {
    std::cout << "=== Array of Animals Test ===" << std::endl;
    const int size = 6;
    Animal* animals[size];

    for (int i = 0; i < size; i++) {
        if (i < size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << "\n=== Deleting Animals ===" << std::endl;
    for (int i = 0; i < size; i++)
        delete animals[i];

    std::cout << "\n=== Deep Copy Test ===" << std::endl;
    Dog dog1;
    dog1.makeSound();
    dog1 = Dog(); // triggers assignment

    Dog dog2(dog1); // triggers copy constructor

    std::cout << "\n=== Deep Copy Verification ===" << std::endl;
    std::cout << "dog1's Brain and dog2's Brain should not point to the same memory address:\n";
    std::cout << "dog1's Brain: " << dog1.getBrain() << std::endl;
    std::cout << "dog2's Brain: " << dog2.getBrain() << std::endl;

    std::cout << "\n=== Individual Allocations ===" << std::endl;
    const Animal* a = new Dog();
    const Animal* b = new Cat();
    delete a;
    delete b;

    std::cout << "\n=== Multiple Cats and Dogs with Custom Brain Data ===" << std::endl;
    Dog d1;
    d1.getBrain()->ideas[0] = "Chase balls!";
    Cat c1;
    c1.getBrain()->ideas[0] = "Catch mice!";

    Dog d2(d1); // Should deep copy brain ideas
    Cat c2(c1); // Should deep copy brain ideas

    // Check that the ideas are independent (deep copy)
    std::cout << "d1's Brain idea: " << d1.getBrain()->ideas[0] << std::endl;
    std::cout << "d2's Brain idea: " << d2.getBrain()->ideas[0] << std::endl;
    std::cout << "c1's Brain idea: " << c1.getBrain()->ideas[0] << std::endl;
    std::cout << "c2's Brain idea: " << c2.getBrain()->ideas[0] << std::endl;

    std::cout << "\n=== Invalid Assignment (Memory Freeing) ===" << std::endl;
    Cat cat1;
    cat1.getBrain()->ideas[0] = "Jump high!";
    Cat cat2;
    cat2 = cat1; // Assignment operator should correctly delete old brain and copy new brain

    return 0;
}

