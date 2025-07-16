/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:54:56 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/10 18:25:31 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>  // rand, srand
#include <ctime>    // time

Base* generate() {
    int r = rand() % 3;
    if (r == 0)
        return new A();
    else if (r == 1)
        return new B();
    else
        return new C();
}

// If p actually points to any of the class, it returns a valid class*
// If not, it returns NULL
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

// If p actually refers to any of the class, it succeeds
// If not, it throws a std::bad_cast exception
// Need to void to avoid warning of result not being used
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
    } catch (...) {
        try {
            (void)dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
        } catch (...) {
            try {
                (void)dynamic_cast<C&>(p);
                std::cout << "C" << std::endl;
            } catch (...) {
                std::cout << "Unknown type" << std::endl;
            }
        }
    }
}

int main() {
    srand(time(NULL)); // random number generator using the current time

    Base* obj = generate();

    std::cout << "Identify from pointer: ";
    identify(obj);

    std::cout << "Identify from reference: ";
    identify(*obj);

    delete obj;
    return 0;
}
