/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:13:45 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/23 13:31:38 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/iter.hpp"

// Print function 
template <typename Type>
void print(const Type& value) {
    std::cout << value << " ";
}

// Increment function 
template <typename Type>
void increment(Type& value) {
    ++value;
}

// toUpp toLow function
template <typename Type>
void change(char& c) {
    if (std::islower(c))
        c = std::toupper(c);
    else
        c = std::tolower(c);
}

int main() {
    // Test 1: Integer array (modifying + printing)
    {
        std::cout << "== Integer Test ==" << std::endl;
        int numbers[] = {1, 2, 3, 4, 5};

        std::cout << "Before increment: ";
        iter(numbers, 3, print<int>);
        std::cout << "\n";

        iter(numbers, 3, increment<int>);

        std::cout << "After increment: ";
        iter(numbers, 3, print<int>);
        std::cout << "\n\n";
    }

    // Test 2: String array (printing only)
    {
        std::cout << "== String Test ==" << std::endl;
        std::string words[] = {"apple", "banana", "cherry"};

        iter(words, 2, print<std::string>);
        std::cout << "\n\n";
    }

    // Test 3: Char array (modifying + printing)
    {
        std::cout << "== Char Test ==" << std::endl;
        char chars[] = {'h', 'E', 'L', 'l', 'o'};

        std::cout << "Before: ";
        iter(chars, 5, print<char>);
        std::cout << "\n";

        iter(chars, 5, change<char>);

        std::cout << "After: ";
        iter(chars, 5, print<char>);
        std::cout << "\n";
    }

    return 0;
}

// int main() {
//     int intArr[] = {1, 2, 3, 4, 5};
//     std::string strArr[] = {"one", "two", "three"};

//     std::cout << "Original intArr: ";
//     iter(intArr, 5, print<int>);
//     std::cout << "\n";

//     iter(intArr, 5, increment<int>);

//     std::cout << "After incrementing intArr: ";
//     iter(intArr, 5, print<int>);
//     std::cout << "\n";

//     std::cout << "String array: ";
//     iter(strArr, 1, print<std::string>);
//     std::cout << "\n";

//     // Example with const array
//     const float floatArr[] = {1.1f, 2.2f, 3.3f};
//     std::cout << "Const float array: ";
//     iter(floatArr, 3, print<float>);
//     std::cout << "\n";

//     return 0;
// }
