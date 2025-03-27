/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:51:06 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/03/27 17:45:14 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main() {
    // Test Case 1: Constructor and toFloat/ToInt Conversion
    std::cout << "Test Case 1: Constructor and toFloat/ToInt Conversion" << std::endl;
    Fixed a(5);        // Integer constructor (5 in fixed-point)
    Fixed b(2.5f);     // Float constructor (2.5 in fixed-point)

    std::cout << "a (as float): " << a.toFloat() << std::endl;   // Should output: 5.0
    std::cout << "a (as int): " << a.toInt() << std::endl;       // Should output: 5

    std::cout << "b (as float): " << b.toFloat() << std::endl;   // Should output: 2.5
    std::cout << "b (as int): " << b.toInt() << std::endl;       // Should output: 2
    std::cout << std::endl;

    // Test Case 2: Comparison Operators
    std::cout << "Test Case 2: Comparison Operators" << std::endl;
    Fixed c(5); // Same as a

    std::cout << "a > b: " << (a > b) << std::endl;   // Should output: 1 (true)
    std::cout << "a < b: " << (a < b) << std::endl;   // Should output: 0 (false)
    std::cout << "a >= b: " << (a >= b) << std::endl; // Should output: 1 (true)
    std::cout << "a <= b: " << (a <= b) << std::endl; // Should output: 0 (false)
    std::cout << "a == c: " << (a == c) << std::endl; // Should output: 1 (true)
    std::cout << "a != b: " << (a != b) << std::endl; // Should output: 1 (true)
    std::cout << std::endl;

    // Test Case 3: Arithmetic Operations
    std::cout << "Test Case 3: Arithmetic Operations" << std::endl;
    Fixed d(3.0f);
    Fixed e(4.5f);

    std::cout << "d + e: " << (d + e) << std::endl;   // Should output: 7.5
    std::cout << "d - e: " << (d - e) << std::endl;   // Should output: -1.5
    std::cout << "d * e: " << (d * e) << std::endl;   // Should output: 13.5
    std::cout << "d / e: " << (d / e) << std::endl;   // Should output: 0.666666 (or similar)
    std::cout << std::endl;

    // Test Case 4: Pre-increment and Post-increment
    std::cout << "Test Case 4: Pre-increment and Post-increment" << std::endl;

    std::cout << "Original value of d: " << d << std::endl;
    std::cout << "Pre-increment: " << ++d << std::endl; // Should output: 4.0
    std::cout << "Post-increment: " << d++ << std::endl; // Should output: 4.0 (before increment)
    std::cout << "After post-increment: " << d << std::endl; // Should output: 5.0
    std::cout << std::endl;

    // Test Case 5: Pre-decrement and Post-decrement
    std::cout << "Test Case 5: Pre-decrement and Post-decrement" << std::endl;

    std::cout << "Original value of e: " << e << std::endl;
    std::cout << "Pre-decrement: " << --e << std::endl; // Should output: 3.5
    std::cout << "Post-decrement: " << e-- << std::endl; // Should output: 3.5 (before decrement)
    std::cout << "After post-decrement: " << e << std::endl; // Should output: 2.5
    std::cout << std::endl;

    // Test Case 6: Static max and min
    std::cout << "Test Case 6: Static max and min" << std::endl;
    Fixed f(10);
    Fixed g(20);

    std::cout << "Max of f and g: " << Fixed::max(f, g) << std::endl; // Should output: 20
    std::cout << "Min of f and g: " << Fixed::min(f, g) << std::endl; // Should output: 10
    std::cout << std::endl;

    // Test Case 7: Handling Division by Zero
    std::cout << "Test Case 7: Handling Division by Zero" << std::endl;
    Fixed h(10);
    Fixed i(0);

    std::cout << "h / i: " << (h / i) << std::endl; // Should output: "Error: Division by zero!"
    std::cout << std::endl;

    return 0;
}


// int main( void ) {
//     Fixed a;
//     Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
    
//     std::cout << a << std::endl;
//     std::cout << ++a << std::endl;
//     std::cout << a << std::endl;
//     std::cout << a++ << std::endl;
//     std::cout << a << std::endl;
    
//     std::cout << b << std::endl;
    
//     std::cout << Fixed::max( a, b ) << std::endl;
    
//     return 0;
// }