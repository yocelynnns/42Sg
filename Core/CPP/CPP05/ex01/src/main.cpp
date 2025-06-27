/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:38:59 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/28 15:19:13 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

int main() {
    std::cout << "\n=== Test 1: Default Constructor ===\n";
    {
        Form f;
        std::cout << f << std::endl;
    }

    std::cout << "\n=== Test 2: Parameterized Constructor - Valid and Invalid ===\n";
    try {
        Form valid("ValidForm", 50, 75);
        std::cout << valid << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        Form tooHigh("TooHighForm", 0, 10); // Invalid
    } catch (std::exception& e) {
        std::cerr << "Expected exception (sign too high): " << e.what() << std::endl;
    }

    try {
        Form tooLow("TooLowForm", 151, 150); // Invalid
    } catch (std::exception& e) {
        std::cerr << "Expected exception (sign too low): " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 3: Copy Constructor ===\n";
    {
        Form original("OriginalForm", 40, 60);
        Form copy(original);
        std::cout << "Copy: " << copy << std::endl;
    }

    std::cout << "\n=== Test 4: Assignment Operator ===\n";
    {
        Form a("FormA", 30, 60);
        Form b("FormB", 50, 100);
        b = a;
        std::cout << "After assignment: " << b << std::endl;
    }

    std::cout << "\n=== Test 5: Getters ===\n";
    {
        Form f("GetterForm", 25, 45);
        std::cout << "Name: " << f.getName() << "\n";
        std::cout << "Signed? " << std::boolalpha << f.getIsSigned() << "\n";
        std::cout << "Sign grade: " << f.getSignGrade() << "\n";
        std::cout << "Exec grade: " << f.getExecGrade() << "\n";
    }

    std::cout << "\n=== Test 6: beSigned() and Exception Handling ===\n";
    {
        Bureaucrat lowRank("LowRank", 100);
        Bureaucrat highRank("HighRank", 20);

        Form form("SignTest", 50, 50);

        // Should fail
        try {
            form.beSigned(lowRank);
        } catch (const std::exception& e) {
            std::cerr << lowRank.getName() << " failed to sign " << form.getName()
                      << ": " << e.what() << std::endl;
        }

        // Should succeed
        try {
            form.beSigned(highRank);
            std::cout << highRank.getName() << " successfully signed " << form.getName() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Unexpected failure: " << e.what() << std::endl;
        }

        std::cout << "Signed status: " << std::boolalpha << form.getIsSigned() << std::endl;
    }

    std::cout << "\n=== Test 7: operator<< Overload ===\n";
    {
        Form printable("PrintableForm", 42, 84);
        std::cout << printable << std::endl;
    }

    return 0;
}
