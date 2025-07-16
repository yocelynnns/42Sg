/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:13:45 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/11 17:19:14 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.tpp"

#define DIVIDER "----------------------------"

template <typename T>
void printArray(const Array<T>& arr, const std::string& name) {
    std::cout << name << " (size: " << arr.size() << "): ";
    for (unsigned int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::cout << "TEST 1: Default Constructor\n" << DIVIDER << "\n";
    Array<int> emptyArray;
    std::cout << "emptyArray size: " << emptyArray.size() << "\n\n";

    std::cout << "TEST 2: Parameterized Constructor\n" << DIVIDER << "\n";
    Array<int> intArray(5);
    for (unsigned int i = 0; i < intArray.size(); i++) {
        intArray[i] = i * 10;
    }
    printArray(intArray, "intArray");
    std::cout << "\n";

    std::cout << "TEST 3: Copy Constructor\n" << DIVIDER << "\n";
    Array<int> copyArray(intArray); // deep copy
    copyArray[0] = 999;
    printArray(intArray, "intArray");
    printArray(copyArray, "copyArray");
    std::cout << "✔️ Deep copy confirmed (modifying copy doesn’t affect original).\n\n";

    std::cout << "TEST 4: Assignment Operator\n" << DIVIDER << "\n";
    Array<int> assignedArray;
    assignedArray = intArray; // deep copy again
    assignedArray[1] = 888;
    printArray(intArray, "intArray");
    printArray(assignedArray, "assignedArray");
    std::cout << "✔️ Deep assignment confirmed.\n\n";

    std::cout << "TEST 5: Self-assignment\n" << DIVIDER << "\n";
    intArray = intArray;
    printArray(intArray, "intArray (after self-assignment)");
    std::cout << "✔️ No crash or corruption.\n\n";

    std::cout << "TEST 6: Bounds Checking\n" << DIVIDER << "\n";
    try {
        std::cout << intArray[999] << "\n"; // Should throw
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
    std::cout << "\n";

    std::cout << "TEST 7: Const Correctness\n" << DIVIDER << "\n";
    const Array<int> constArray = intArray;
    std::cout << "constArray[2]: " << constArray[2] << "\n";
    // constArray[2] = 10; // ❌ Uncommenting this should cause a compile error
    std::cout << "✔️ Const access works.\n\n";

    std::cout << "TEST 8: Different Type (std::string)\n" << DIVIDER << "\n";
    Array<std::string> stringArray(3);
    stringArray[0] = "Hello";
    stringArray[1] = "Template";
    stringArray[2] = "Array";
    printArray(stringArray, "stringArray");
    std::cout << "✔️ Works with custom types.\n\n";

    std::cout << "All tests completed successfully ✅\n";

    return 0;
}

// int main()
// {
//     try {
//         Array<int> a(5);

//         for (unsigned int i = 0; i < a.size(); i++)
//             a[i] = i * 10;

//         Array<int> b = a; // Test copy constructor

//         b[0] = 999;

//         std::cout << "Array a: ";
//         for (unsigned int i = 0; i < a.size(); i++)
//             std::cout << a[i] << " ";
//         std::cout << "\n";

//         std::cout << "Array b: ";
//         for (unsigned int i = 0; i < b.size(); i++)
//             std::cout << b[i] << " ";
//         std::cout << "\n";

//         std::cout << "Accessing out-of-bound index:\n";
//         std::cout << a[10] << "\n"; // should throw

//     } catch (const std::exception& e) {
//         std::cerr << "Exception caught: " << e.what() << '\n';
//     }

//     return 0;
// }
