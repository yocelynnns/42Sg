/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:00:43 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/10 17:24:04 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    // Serializer a; // Cannot instantiate
    
    // Create a Data object
    Data original;
    original.id = 42;
    original.name = "Hello";

    // Serialize the pointer
    uintptr_t raw = Serializer::serialize(&original);

    // Deserialize it back to a Data*
    Data* recovered = Serializer::deserialize(raw);

    // Verify
    std::cout << "Original pointer: " << &original << std::endl;
    std::cout << "Recovered pointer: " << recovered << std::endl;

    if (recovered == &original)
        std::cout << "Success: The pointers match" << std::endl;
    else
        std::cout << "Error: The pointers doesnt match" << std::endl;

    // Print
    std::cout << "Recovered Data -> id: " << recovered->id
              << ", name: " << recovered->name << std::endl;

    return 0;
}
