/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:56:46 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/07/29 16:34:49 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int main()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << "top: " << mstack.top() << std::endl;
    std::cout << "--------------" << std::endl;
    mstack.pop();
    std::cout << "size: " << mstack.size() << std::endl;
    std::cout << "--------------" << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    //[...]
    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    std::cout << "Stack:" << std::endl;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);
    return 0;
}

// #include <list>
// #include <string>

// int main() {
//     std::cout << "=== Test 1: Test for MutantStack ===" << std::endl;
//     MutantStack<int> mstack;
//     mstack.push(5);
//     mstack.push(17);
//     std::cout << "top: " << mstack.top() << std::endl;
//     mstack.pop();
//     std::cout << "size: " << mstack.size() << std::endl;
//     mstack.push(3);
//     mstack.push(5);
//     mstack.push(737);
//     mstack.push(0);

//     std::cout << "\nStack:" << std::endl;
//     for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
//         std::cout << *it << std::endl;

//     std::cout << "\n=== Compare with std::list ===" << std::endl;
//     std::list<int> lst;
//     lst.push_back(5);
//     lst.push_back(17);
//     std::cout << "top: " << lst.back() << std::endl;
//     lst.pop_back();
//     std::cout << "size: " << lst.size() << std::endl;
//     lst.push_back(3);
//     lst.push_back(5);
//     lst.push_back(737);
//     lst.push_back(0);

//     std::cout << "\nStack:" << std::endl;
//     for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
//         std::cout << *it << std::endl;

//     std::cout << "\n=== Test 2: MutantStack<char> ===" << std::endl;
//     MutantStack<char> charStack;
//     charStack.push('A');
//     charStack.push('B');
//     charStack.push('C');

//     for (MutantStack<char>::iterator it = charStack.begin(); it != charStack.end(); ++it)
//         std::cout << *it << " ";
//     std::cout << std::endl;

//     std::cout << "\n=== Test 3: MutantStack<std::string> ===" << std::endl;
//     MutantStack<std::string> strStack;
//     strStack.push("Hello");
//     strStack.push("Mutant");
//     strStack.push("Stack");
//     for (MutantStack<std::string>::iterator it = strStack.begin(); it != strStack.end(); ++it)
//         std::cout << *it << std::endl;

//     std::cout << "\n=== Test 4: Reverse Iteration ===" << std::endl;
//     for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
//         std::cout << *rit << std::endl;

//     std::cout << "\n=== Test 5: Copy constructor & assignment ===" << std::endl;
//     MutantStack<int> copyStack(mstack);
//     std::cout << "Copy:" << std::endl;
//     for (MutantStack<int>::iterator it = copyStack.begin(); it != copyStack.end(); ++it)
//         std::cout << *it << std::endl;

//     MutantStack<int> assignStack;
//     assignStack = mstack;
//     std::cout << "\nAssigned:" << std::endl;
//     for (MutantStack<int>::iterator it = assignStack.begin(); it != assignStack.end(); ++it)
//         std::cout << *it << std::endl;

//     return 0;
// }
