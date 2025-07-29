/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:13:45 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/23 13:59:32 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Array.hpp>

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
}

// template <typename T>
// void printArray(const Array<T>& arr, const std::string& name) {
//     std::cout << name << " (size: " << arr.size() << "): ";
//     for (unsigned int i = 0; i < arr.size(); i++) {
//         std::cout << arr[i] << " ";
//     }
//     std::cout << "\n";
// }

// int main() {
//     std::cout << "TEST 1: Default Constructor\n";
//     std::cout << "----------------------------" << "\n";
//     Array<int> emptyArray;
//     std::cout << "emptyArray size: " << emptyArray.size() << "\n\n";

//     std::cout << "TEST 2: Parameterized Constructor\n";
//     std::cout << "----------------------------" << "\n";
//     Array<int> intArray(5);
//     for (unsigned int i = 0; i < intArray.size(); i++) {
//         intArray[i] = i * 10;
//     }
//     printArray(intArray, "intArray");
//     std::cout << "\n";

//     std::cout << "TEST 3: Copy Constructor\n";
//     std::cout << "----------------------------" << "\n";
//     Array<int> copyArray(intArray);
//     copyArray[0] = 999;
//     printArray(intArray, "intArray");
//     printArray(copyArray, "copyArray");
//     std::cout << "\n";

//     std::cout << "TEST 4: Bounds Checking\n";
//     std::cout << "----------------------------" << "\n";
//     try {
//         std::cout << intArray[999] << "\n";
//     } catch (const std::exception& e) {
//         std::cout << "Caught exception: " << e.what() << "\n";
//     }
//     std::cout << "\n";

//     std::cout << "TEST 5: Const Correctness\n";
//     std::cout << "----------------------------" << "\n";
//     const Array<int> constArray = intArray;
//     std::cout << "constArray[2]: " << constArray[2] << "\n";
//     // constArray[2] = 10; // compile error
//     std::cout << "\n";

//     std::cout << "TEST 6: Different Type (std::string)\n";
//     std::cout << "----------------------------" << "\n";
//     Array<std::string> stringArray(3);
//     stringArray[0] = "Hello";
//     stringArray[1] = "Template";
//     stringArray[2] = "Array";
//     printArray(stringArray, "stringArray");

//     return 0;
// }

// int main()
// {
//     try {
//         Array<int> a(5);

//         for (unsigned int i = 0; i < a.size(); i++)
//             a[i] = i * 10;

//         Array<int> b = a;

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
//         std::cout << a[10] << "\n";

//     } catch (const std::exception& e) {
//         std::cerr << "Exception caught: " << e.what() << '\n';
//     }

//     return 0;
// }
