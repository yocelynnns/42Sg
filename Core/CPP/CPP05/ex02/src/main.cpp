/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:59:54 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/06/27 20:59:50 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    std::cout << "========== FORM TESTS ==========\n";

    // TEST 1: Executing an unsigned form
    try {
        std::cout << "\n[TEST 1] Executing an unsigned form (should throw FormNotSignedException)\n";
        PresidentialPardonForm f1("Marvin");
        Bureaucrat b1("Alice", 1);
        b1.executeForm(f1);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // TEST 2: Signing with low grade
    try {
        std::cout << "\n[TEST 2] Signing with too low grade (should fail)\n";
        RobotomyRequestForm f2("Wall-E");
        Bureaucrat b2("Bob", 100); // Grade too low to sign (needs <= 72)
        b2.signForm(f2);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // TEST 3: Proper signing and execution of ShrubberyCreationForm
    try {
        std::cout << "\n[TEST 3] Signing and executing ShrubberyCreationForm\n";
        ShrubberyCreationForm f3("yard");
        Bureaucrat b3("Charlie", 130); // Valid signer and executor
        b3.signForm(f3);
        b3.executeForm(f3);
        std::cout << "Check for 'yard_shrubbery' file with ASCII art.\n";
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // TEST 4: Executing with insufficient grade
    try {
        std::cout << "\n[TEST 4] Execution denied due to low grade\n";
        PresidentialPardonForm f4("Trillian");
        Bureaucrat signer("Dave", 1);    // Valid signer
        Bureaucrat executor("Eve", 50);  // Invalid executor (needs <= 5)
        signer.signForm(f4);
        executor.executeForm(f4);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // TEST 5: RobotomyRequestForm random success/failure
    try {
        std::cout << "\n[TEST 5] Robotomy execution randomness\n";
        RobotomyRequestForm f5("C3PO");
        Bureaucrat b6("Frank", 1); // Can sign and execute
        b6.signForm(f5);
        for (int i = 0; i < 5; ++i) {
            std::cout << "\nAttempt #" << i + 1 << ":\n";
            b6.executeForm(f5);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    // TEST 6: Proper signing and execution of PresidentialPardonForm
    try {
        std::cout << "\n[TEST 6] Proper signing and execution of PresidentialPardonForm\n";
        PresidentialPardonForm f6("Snowden"); // target of the pardon

        Bureaucrat b9("Trump", 1); // High enough grade for both signing and execution

        b9.signForm(f6);
        b9.executeForm(f6);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    // TEST 7: Bureaucrat grade boundaries
    try {
        std::cout << "\n[TEST 7] Bureaucrat grade limits\n";
        Bureaucrat tooHigh("God", 0); // Should throw
    } catch (std::exception& e) {
        std::cerr << "Exception (Too High): " << e.what() << "\n";
    }

    try {
        Bureaucrat tooLow("Mortal", 151); // Should throw
    } catch (std::exception& e) {
        std::cerr << "Exception (Too Low): " << e.what() << "\n";
    }

    return 0;
}
