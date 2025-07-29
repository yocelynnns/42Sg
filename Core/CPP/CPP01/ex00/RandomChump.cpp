/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:40:09 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/20 16:57:37 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void RandomChump(std::string name) {
    Zombie zombie(name); // Allocate on the stack
    zombie.Announce(); // Announce the zombie
    // Zombie is automatically destroyed when it goes out of scope
}