/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:56:46 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/07/29 16:32:29 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Span.hpp"

int main()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    return 0;
}

// int main() {
//     Span sp(10000);
//     std::vector<int> bigNumbers;

//     for (int i = 0; i < 10000; ++i)
//         bigNumbers.push_back(i * 2);

//     sp.addNumbers(bigNumbers.begin(), bigNumbers.end());

//     std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
//     std::cout << "Longest Span: " << sp.longestSpan() << std::endl;

//     return 0;
// }

// int main()
// {
//     Span sp = Span(5);

//     std::cout << "------TEST FOR EMPTY SHORTEST/LONGEST SPAN" << std::endl;
//     try {
//         std::cout << "Shortest Span (empty): " << sp.shortestSpan() << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Expected exception (shortestSpan): " << e.what() << std::endl;
//     }

//     try {
//         std::cout << "Longest Span (empty): " << sp.longestSpan() << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Expected exception (longestSpan): " << e.what() << std::endl;
//     }

//     std::cout << "\n------ADD NUMBERS------" << std::endl;
//     try {
//         sp.addNumber(6);
//         sp.addNumber(3);
//         sp.addNumber(17);
//         sp.addNumber(9);
//         sp.addNumber(11);
//     } catch (const std::exception& e) {
//         std::cerr << "Unexpected exception while adding: " << e.what() << std::endl;
//         return 1;
//     }

//     std::cout << "\n------TEST FOR ADDING BEYOND LIMIT------" << std::endl;
//     try {
//         sp.addNumber(10);
//     } catch (const std::exception& e) {
//         std::cerr << "Expected exception (add beyond limit): " << e.what() << std::endl;
//     }

//     std::cout << "\n------PRINT VECTOR CONTENTS------" << std::endl;
//     std::cout << "Vector contents:" << std::endl;
//     for (std::vector<int>::const_iterator it = sp.getData().begin(); it != sp.getData().end(); ++it)
//         std::cout << *it << std::endl;

//     std::cout << "\n------SPAN CALCULATIONS------" << std::endl;
//     std::cout << "Shortest Span (expected 2): " << sp.shortestSpan() << std::endl;
//     std::cout << "Longest Span (expected 14): " << sp.longestSpan() << std::endl;

//     return 0;
// }
