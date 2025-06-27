/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:40:21 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 20:45:20 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Set.hpp"
#include "ArrayBag.hpp"
#include "TreeBag.hpp"
#include <iostream>

int main() {
    std::cout << "=== ArrayBag via Set ===\n";
    SearchableBag* arrBag = static_cast<SearchableBag*>(new ArrayBag());
    arrBag->insert(1);
    arrBag->insert(2);
    arrBag->insert(3);
    Set set1(arrBag);
    set1.print();
    std::cout << "Has 2? " << (set1.has(2) ? "Yes" : "No") << "\n";

    std::cout << "\n=== TreeBag via Set ===\n";
    SearchableBag* treeBag = static_cast<SearchableBag*>(new TreeBag());
    treeBag->insert(10);
    treeBag->insert(5);
    treeBag->insert(15);
    Set set2(treeBag);
    set2.print();
    std::cout << "Has 7? " << (set2.has(7) ? "Yes" : "No") << "\n";

    std::cout << "\n=== OCF Test: Copy Constructor ===\n";
    Set copySet(set1); // copy constructor
    copySet.print();
    std::cout << "CopySet has 3? " << (copySet.has(3) ? "Yes" : "No") << "\n";

    std::cout << "\n=== OCF Test: Copy Assignment ===\n";
    Set assignedSet = set2; // copy assignment
    assignedSet.print();
    std::cout << "AssignedSet has 15? " << (assignedSet.has(15) ? "Yes" : "No") << "\n";

    std::cout << "\n=== Done! Destructors will now be called ===\n";
    return 0;
}
