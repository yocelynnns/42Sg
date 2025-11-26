/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 03:07:04 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/19 14:43:14 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void Harl::debug() {
    std::cout << "DEBUG: I love having extra bacon for my";
    std::cout << "7XL-double-cheese-triple-pickle-";
    std::cout << "specialketchup burger. I really do!" << std::endl;
};

void Harl::info() {
    std::cout << "INFO: I cannot believe adding extra bacon costs more";
    std::cout << " money. You didn't put enough bacon in my burger!";
    std::cout << " If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning() {
    std::cout << "WARNING: I think I deserve to have some extra bacon for ";
    std::cout << "free. I've been coming for years, whereas you";
    std::cout << " started working here just last month." << std::endl;
}

void Harl::error() {
    std::cout << "ERROR: This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level) {
    // Array of function pointers
    void (Harl::*complaints[])(void) = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };
    // Array of string complaint levels
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR"};
    for (int i = 0; i < 4; ++i) {
        if (levels[i] == level) {
            (this->*complaints[i])();
            return;
        }
    }
    std::cout << "ELSE: Invalid complaint level!" << std::endl;
}