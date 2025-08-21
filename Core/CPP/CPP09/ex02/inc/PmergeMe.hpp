/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:13:29 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/08/14 14:11:22 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <sys/time.h>

class PmergeMe
{
    public:
        PmergeMe();
        ~PmergeMe();

        static std::vector<int> parseInput(int argc, char **argv);
        static double getTimeUs();
        static void sortVector(std::vector<int>& v);
        static void sortDeque(std::deque<int>& d);

    private:
        struct Pair {
            int big;
            int small;
            Pair():big(0),small(0) {}
            Pair(int B,int S):big(B),small(S) {}
        };

        // === Core algorithm (templated, but we explicitly instantiate for vector/deque) ===
        template<typename Container>
        static void mergeInsertSort(Container& cont);

        // Make (big, small) pairs + straggler
        template<typename Container>
        static void makePairs(const Container& cont, std::vector<Pair>& pairs, bool& hasStraggler, int& straggler);

        // Stable merge-sort for pairs by 'big' (preserve links big<->small)
        static void mergeSortPairs(std::vector<Pair>& pairs);
        static void mergePairs(std::vector<Pair>& a, std::vector<Pair>& b, std::vector<Pair>& out);

        // Jacobsthal insertion order for indices 1..m-1
        static std::vector<size_t> jacobsOrder(size_t m);

        // Lower_bound index in [0, endIndex) within a random-access container
        template<typename Container>
        static size_t lowerBoundIndex(const Container& chain, size_t endIndex, int value);

        // Insert at index in random-access container
        template<typename Container>
        static void insertAt(Container& chain, size_t idx, int value);

        // Update partner positions after an insertion at idx
        static void updatePos(std::vector<size_t>& pos, size_t idx);
};

#endif
