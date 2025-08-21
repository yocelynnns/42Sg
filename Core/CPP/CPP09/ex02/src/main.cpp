/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:13:21 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/08/14 14:47:46 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static void printCont(const std::vector<int>& v) {
    const size_t n = v.size();
    if (n <= 10) {
        for (size_t i = 0; i < n; ++i)
            std::cout << v[i] << " ";
    } else {
        for (size_t i = 0; i < 5 && i < n; ++i)
            std::cout << v[i] << " ";
        std::cout << "[...] ";
    }
}

int main(int argc, char **argv) {
    try {
        std::vector<int> input = PmergeMe::parseInput(argc, argv);
        if (input.empty())
            throw std::invalid_argument("Error");

        std::cout << "Before: ";
        printCont(input);
        std::cout << std::endl;

        std::vector<int> v = input;
        std::deque<int>  d(input.begin(), input.end());

        double t0 = PmergeMe::getTimeUs();
        PmergeMe::sortVector(v);
        double t1 = PmergeMe::getTimeUs();

        double t2 = PmergeMe::getTimeUs();
        PmergeMe::sortDeque(d);
        double t3 = PmergeMe::getTimeUs();

        std::cout << "After: ";
        printCont(v);
        std::cout << std::endl;

        std::cout << "Time to process a range of " << v.size()
                  << " elements with std::vector : "
                  << std::fixed << std::setprecision(5) << (t1 - t0)/1e6 << " us" << std::endl;

        std::cout << "Time to process a range of " << d.size()
                  << " elements with std::deque : "
                  << std::fixed << std::setprecision(5) << (t3 - t2)/1e6 << " us" << std::endl;

    } catch (std::exception&) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}
