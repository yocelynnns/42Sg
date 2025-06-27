/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:38:59 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/28 14:29:43 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
    std::cout << "=== Test 1: Constructing with boundary values ===" << std::endl;
    try {
        Bureaucrat top("Top", 1);
        std::cout << top << std::endl;

        Bureaucrat bottom("Bottom", 150);
        std::cout << bottom << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in Test 1: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: Invalid construction values ===" << std::endl;
    try {
        Bureaucrat tooHigh("TooHigh", 0);
    } catch (const std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << std::endl;
    }

    try {
        Bureaucrat tooLow("TooLow", 151);
    } catch (const std::exception& e) {
        std::cerr << "Expected exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 3: Increment and decrement with edge cases ===" << std::endl;
    try {
        Bureaucrat john("John", 2);
        std::cout << john << std::endl;
        john.incGrade(); // Should become 1
        std::cout << "After increment: " << john << std::endl;
        john.incGrade(); // Should throw
    } catch (const std::exception& e) {
        std::cerr << "Exception during increment: " << e.what() << std::endl;
    }

    try {
        Bureaucrat jane("Jane", 149);
        std::cout << jane << std::endl;
        jane.decGrade(); // Should become 150
        std::cout << "After decrement: " << jane << std::endl;
        jane.decGrade(); // Should throw
    } catch (const std::exception& e) {
        std::cerr << "Exception during decrement: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 4: Copy Constructor and Assignment Operator ===" << std::endl;
    try {
        Bureaucrat original("Original", 75);
        Bureaucrat copyConstructed(original);
        std::cout << "Copy Constructed: " << copyConstructed << std::endl;

        Bureaucrat another("Another", 100);
        another = original;
        std::cout << "After assignment: " << another << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in copy tests: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 5: Constant Name Protection Check ===" << std::endl;
    try {
        Bureaucrat a("Alpha", 50);
        Bureaucrat b("Beta", 100);
        b = a; // Name should still be "Beta"
        std::cout << "b's name should still be Beta: " << b.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in const name test: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 6: Operator<< Overload ===" << std::endl;
    try {
        Bureaucrat reporter("Reporter", 10);
        std::cout << "Using << overload: " << reporter << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in operator<< test: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 7: Multiple Bureaucrats in a Loop ===" << std::endl;
    try {
        for (int i = 145; i <= 150; ++i) {
            Bureaucrat b("LoopGuy", i);
            std::cout << b << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in loop test: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 8: Stress Test Upper and Lower Boundaries ===" << std::endl;
    try {
        Bureaucrat up("Upper", 2);
        up.incGrade(); // to 1
        up.incGrade(); // should throw
    } catch (const std::exception& e) {
        std::cerr << "Stress test upper bound: " << e.what() << std::endl;
    }

    try {
        Bureaucrat low("Lower", 149);
        low.decGrade(); // to 150
        low.decGrade(); // should throw
    } catch (const std::exception& e) {
        std::cerr << "Stress test lower bound: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 9: Destructor Output Test ===" << std::endl;
    {
        Bureaucrat temp("Scoped", 10);
    } // Should print destruction message here

    std::cout << "\n=== Test 10: getName(), getGrade(), and Default Constructor ===" << std::endl;
    try {
        Bureaucrat defaultBureaucrat;
        std::cout << "Default Bureaucrat: " << defaultBureaucrat << std::endl;

        std::cout << "getName(): " << defaultBureaucrat.getName() << std::endl;
        std::cout << "getGrade(): " << defaultBureaucrat.getGrade() << std::endl;

        Bureaucrat custom("Custom", 42);
        std::cout << "Custom Bureaucrat: " << custom << std::endl;

        std::cout << "getName(): " << custom.getName() << std::endl;
        std::cout << "getGrade(): " << custom.getGrade() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception in getName/getGrade/default test: " << e.what() << std::endl;
    }
    
    return 0;
}

