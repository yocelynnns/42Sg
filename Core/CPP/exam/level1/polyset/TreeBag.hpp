/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeBag.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:39:36 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/02 14:47:11 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEBAG_HPP
#define TREEBAG_HPP

#include "SearchableBag.hpp"
#include <iostream>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : value(v), left(0), right(0) {}  
};

class TreeBag : public SearchableBag {
private:
    TreeNode* root;
    int count;

    void insert(TreeNode*& node, int value);
    void print(TreeNode* node) const;
    bool has(TreeNode* node, int value) const;
    void destroy(TreeNode* node);
    TreeNode* clone(TreeNode* node);

public:
    TreeBag();
    TreeBag(const TreeBag& other);
    TreeBag& operator=(const TreeBag& other);
    ~TreeBag();

    void insert(int value);
    int size() const;
    void print() const;
    bool has(int value) const;
};

#endif
