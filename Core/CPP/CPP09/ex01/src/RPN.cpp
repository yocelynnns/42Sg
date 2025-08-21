/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:13:01 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/08/14 14:38:35 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) {
    *this = other;
}

RPN &RPN::operator=(const RPN &other) {
    (void)other;
    return *this;
}

RPN::~RPN() {}

int RPN::count(const std::string &arg)
{
    std::stack<int> st;
    std::stringstream ss(arg);
    std::string token;

    while (ss >> token)
    {
        // Check if token is an operator
        if (token.size() == 1 && std::string("+-*/").find(token) != std::string::npos)
        {
            if (st.size() < 2)
                throw std::runtime_error("Error");
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            st.push(applyOp(a, b, token[0]));
        }
        // Check if token is a number
        else if (token.size() == 1 && std::isdigit(token[0])) {
            st.push(token[0] - '0');
        }
        else {
            throw std::runtime_error("Error");
        }
    }

    if (st.size() != 1)
        throw std::runtime_error("Error");

    return st.top();
}

int RPN::applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Error");
            return a / b;
    }
    throw std::runtime_error("Error");
}
