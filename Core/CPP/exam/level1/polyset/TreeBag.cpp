/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeBag.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:39:50 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/23 20:43:09 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TreeBag.hpp"
#include <iostream>

TreeBag::TreeBag() : root(0), count(0) {}

TreeBag::~TreeBag() {
    destroy(root);
}

TreeBag::TreeBag(const TreeBag& other) : root(0), count(0) {
    root = clone(other.root);
    count = other.count;
}

TreeBag& TreeBag::operator=(const TreeBag& other) {
    if (this != &other) {
        destroy(root);
        root = clone(other.root);
        count = other.count;
    }
    return *this;
}

TreeNode* TreeBag::clone(TreeNode* node) {
    if (!node) return 0;
    TreeNode* newNode = new TreeNode(node->value);
    newNode->left = clone(node->left);
    newNode->right = clone(node->right);
    return newNode;
}

void TreeBag::destroy(TreeNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void TreeBag::insert(TreeNode*& node, int value) {
    if (!node) {
        node = new TreeNode(value);
        count++;
    } else if (value < node->value) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

void TreeBag::insert(int value) {
    insert(root, value);
}

int TreeBag::size() const {
    return count;
}

void TreeBag::print(TreeNode* node) const {
    if (!node) return;
    print(node->left);
    std::cout << node->value << " ";
    print(node->right);
}

void TreeBag::print() const {
    std::cout << "TreeBag: ";
    print(root);
    std::cout << std::endl;
}

bool TreeBag::has(TreeNode* node, int value) const {
    if (!node) return false;
    if (value == node->value) return true;
    if (value < node->value)
        return has(node->left, value);
    else
        return has(node->right, value);
}

bool TreeBag::has(int value) const {
    return has(root, value);
}
