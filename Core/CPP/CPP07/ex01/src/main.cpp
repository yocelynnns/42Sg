/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:13:45 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/11 16:28:40 by yocelynnns       ###   ########.fr       */
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

int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    std::string strArr[] = {"one", "two", "three"};

    std::cout << "Original intArr: ";
    iter(intArr, 5, print<int>);
    std::cout << "\n";

    iter(intArr, 5, increment<int>);

    std::cout << "After incrementing intArr: ";
    iter(intArr, 5, print<int>);
    std::cout << "\n";

    std::cout << "String array: ";
    iter(strArr, 1, print<std::string>);
    std::cout << "\n";

    // Example with const array
    const float floatArr[] = {1.1f, 2.2f, 3.3f};
    std::cout << "Const float array: ";
    iter(floatArr, 3, print<float>);
    std::cout << "\n";

    return 0;
}
