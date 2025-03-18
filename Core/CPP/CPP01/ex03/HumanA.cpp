/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:05:03 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/17 18:25:12 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) : Name(name), weapon(weapon) {}

void HumanA::attack() {
    std::cout << Name << " attacks with their " << weapon.getType() << std::endl;
};