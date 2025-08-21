/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:13:27 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/08/14 15:38:11 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

double PmergeMe::getTimeUs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1e6 + tv.tv_usec;
}

// ====== PARSING ======
std::vector<int> PmergeMe::parseInput(int argc, char **argv)
{
    std::vector<int> res;
    for (int i = 1; i < argc; ++i)
    {
        std::string s(argv[i]);
        if (s.empty())
            throw std::invalid_argument("Error");
        for (size_t j = 0; j < s.size(); ++j)
        {
            if (!std::isdigit(static_cast<unsigned char>(s[j])))
                throw std::invalid_argument("Error");
        }
        long val = std::atol(s.c_str());
        if (val <= 0 || val > INT_MAX)
            throw std::invalid_argument("Error");
        res.push_back(static_cast<int>(val));
    }
    return res;
}

void PmergeMe::sortVector(std::vector<int>& v) { mergeInsertSort(v); }
void PmergeMe::sortDeque (std::deque<int>&  d) { mergeInsertSort(d);  }

// ====== PAIRS ======
template<typename Container>
void PmergeMe::makePairs(const Container& container, std::vector<Pair>& pairs, bool& hasRemain, int& remains) {
    pairs.clear();
    hasRemain = false;
    remains = 0;

    size_t n = container.size();
    if (n == 0)
        return;

    if (n % 2 != 0) {
        hasRemain = true;
        remains = container[n - 1];
        n -= 1;
    }
    for (size_t i = 0; i < n; i += 2) {
        int a = container[i];
        int b = container[i + 1];
        if (a >= b)
            pairs.push_back(Pair(a, b));
        else
            pairs.push_back(Pair(b, a));
    }
}

// ====== MERGE-SORT PAIRS ======
void PmergeMe::mergeSortPairs(std::vector<Pair>& pairs)
{
    if (pairs.size() <= 1)
            return;

    size_t mid = pairs.size() / 2;
    std::vector<Pair> left(pairs.begin(), pairs.begin() + mid);
    std::vector<Pair> right(pairs.begin() + mid, pairs.end());
    mergeSortPairs(left);
    mergeSortPairs(right);
    std::vector<Pair> merged;
    mergePairs(left, right, merged);
    pairs.swap(merged);
}

void PmergeMe::mergePairs(std::vector<Pair>& a, std::vector<Pair>& b, std::vector<Pair>& res)
{
    res.clear();
    size_t i = 0;
    size_t j = 0;
    while (i < a.size() && j < b.size())
    {
        if (a[i].big <= b[j].big)
        {
            res.push_back(a[i]);
            ++i;
        }
        else
        {
            res.push_back(b[j]);
            ++j;
        }
    }
    while (i < a.size())
    {
        res.push_back(a[i]);
        ++i;
    }
    while (j < b.size())
    {
        res.push_back(b[j]);
        ++j;
    }
}

// ====== JACOBSTHAL ======
std::vector<size_t> PmergeMe::jacobsOrder(size_t m)
{
    static const size_t jacobSeq[] = {
        0, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683,
        1365, 2731, 5461, 10923, 21845, 43691, 87381,
        174763, 349525, 699051, 1398101, 2796203, 5592405
    };
    static const size_t seq_len = sizeof(jacobSeq) / sizeof(jacobSeq[0]);

    std::vector<size_t> res;
    if (m <= 1)
        return res;

    res.push_back(1); // insert index 1 right after index 0

    size_t prev = 1; // lower bound (prev jacobsthal)
    for (size_t i = 2; i < seq_len && jacobSeq[i] < m; ++i)
    {
        size_t hi = jacobSeq[i]; //upper bound (curr jacobsthal or m-1 if it exceeds m)
        if (hi >= m)
            hi = m - 1;

        // push (prev, hi] in descending order
        for (size_t idx = hi; idx > prev; --idx)
            res.push_back(idx);

        prev = jacobSeq[i];
    }

    if (prev < m - 1)
    {
        for (size_t idx = m - 1; idx > prev; --idx)
            res.push_back(idx);
    }

    return res;
}

// ====== lower_bound index in [0, endIndex) ======
template<typename Container>
size_t PmergeMe::lowerBoundIndex(const Container& chain, size_t endIndex, int value)
{
    // standard binary search for first position >= value
    size_t lo = 0;
    size_t hi = endIndex;
    while (lo < hi)
    {
        size_t mid = lo + (hi - lo) / 2;
        if (chain[mid] < value)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

template<typename Container>
void PmergeMe::insertAt(Container& chain, size_t idx, int value) {
    typename Container::iterator it = chain.begin() + static_cast<typename Container::difference_type>(idx);
    chain.insert(it, value);
}

void PmergeMe::updatePos(std::vector<size_t>& pos, size_t idx) {
    for (size_t k = 0; k < pos.size(); ++k) {
        if (pos[k] >= idx)
            pos[k] += 1;
    }
}

// ====== MERGE INSERT (Ford–Johnson) ======
template<typename Container>
void PmergeMe::mergeInsertSort(Container& container)
{
    if (container.size() <= 1)
        return;

    // (1) Pairing
    std::vector<Pair> pairs;
    bool hasRemain = false;
    int  remains = 0;
    makePairs(container, pairs, hasRemain, remains);

    // (2) Merge-sort the pairs by their 'big' (preserve big/small links)
    mergeSortPairs(pairs);

    // (3) Build main chain from sorted bigs, track partner positions
    Container mainChain;
    std::vector<size_t> partnerPos(pairs.size(), 0);
    for (size_t i = 0; i < pairs.size(); ++i) {
        mainChain.push_back(pairs[i].big);
        partnerPos[i] = i; // initial position of each big in the chain
    }

    // (4) Insert the first small (index 0) bounded to its partner
    if (!pairs.empty()) {
        size_t bound = partnerPos[0];           // current index of its big
        size_t ins   = lowerBoundIndex(mainChain, bound, pairs[0].small);
        insertAt(mainChain, ins, pairs[0].small);
        updatePos(partnerPos, ins);         // all bigs at/after ins shift right
    }

    // (5) Insert remaining smalls in Jacobsthal order, each bounded by its partner
    std::vector<size_t> order = jacobsOrder(pairs.size());
    for (size_t t = 0; t < order.size(); ++t)
    {
        size_t i = order[t];                    // pair index to insert smalls
        if (i >= pairs.size())
            continue;
        size_t bound = partnerPos[i];           // can't search past its big
        size_t ins   = lowerBoundIndex(mainChain, bound, pairs[i].small);
        insertAt(mainChain, ins, pairs[i].small);
        updatePos(partnerPos, ins);         // update all stored big positions
    }

    // (6) Insert remains into full chain
    if (hasRemain)
    {
        size_t ins = lowerBoundIndex(mainChain, mainChain.size(), remains);
        insertAt(mainChain, ins, remains);
        // no need to maintain partnerPos anymore
    }

    // (7) Move result back into original container
    container = mainChain;
}

// ====== Explicit template instantiations (needed because impl in .cpp) ======
template void PmergeMe::mergeInsertSort<std::vector<int> >(std::vector<int>&);
template void PmergeMe::mergeInsertSort<std::deque<int> >(std::deque<int>&);
template void PmergeMe::makePairs<std::vector<int> >(const std::vector<int>&, std::vector<Pair>&, bool&, int&);
template void PmergeMe::makePairs<std::deque<int>  >(const std::deque<int>&,  std::vector<Pair>&, bool&, int&);
template size_t PmergeMe::lowerBoundIndex<std::vector<int> >(const std::vector<int>&, size_t, int);
template size_t PmergeMe::lowerBoundIndex<std::deque<int>  >(const std::deque<int>&,  size_t, int);
template void PmergeMe::insertAt<std::vector<int> >(std::vector<int>&, size_t, int);
template void PmergeMe::insertAt<std::deque<int>  >(std::deque<int>&,  size_t, int);
