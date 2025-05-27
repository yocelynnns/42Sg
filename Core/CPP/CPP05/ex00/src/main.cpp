/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:38:59 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/05/27 20:39:20 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
    try {
        Bureaucrat bob("Bob", 2);
        std::cout << bob << std::endl;

        bob.incGrade(); // Should become 1
        std::cout << "After increment: " << bob << std::endl;

        bob.incGrade(); // Should throw
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        Bureaucrat tom("Tom", 151); // Invalid, should throw
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught during Tom creation: " << e.what() << std::endl;
    }

    try {
        Bureaucrat alice("Alice", 149);
        std::cout << alice << std::endl;

        alice.decGrade(); // Should be 150
        std::cout << "After decrement: " << alice << std::endl;

        alice.decGrade(); // Should throw
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught with Alice: " << e.what() << std::endl;
    }

    return 0;
}
