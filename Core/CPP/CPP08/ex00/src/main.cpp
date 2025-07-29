/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:56:46 by ysetiawa          #+#    #+#             */
/*   Updated: 2025/07/25 13:25:54 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main() {
    std::cout << "-------- test for vector --------" << std::endl;
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    try {
        std::cout << "Found: " << *easyfind(v, 3) << std::endl;
        std::cout << "Found: " << *easyfind(v, 10) << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "-------- test for list --------" << std::endl;
    std::list<int> l;
    l.push_back(5);
    l.push_back(4);
    l.push_back(3);
    l.push_back(2);
    l.push_back(1);
    try {
        std::cout << "Found: " << *easyfind(l, 2) << std::endl;
        std::cout << "Found: " << *easyfind(l, 6) << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "-------- test for deque --------" << std::endl;
    std::deque<int> d;
    d.push_back(7);
    d.push_back(8);
    d.push_back(9);
    d.push_back(10);
    try {
        std::cout << "Found: " << *easyfind(d, 8) << std::endl;
        std::cout << "Found: " << *easyfind(d, 0) << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
