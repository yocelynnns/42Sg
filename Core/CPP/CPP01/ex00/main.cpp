/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:40:05 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/03/20 16:55:05 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main() {
    // zombie on the heap
    Zombie *zombie1 = NewZombie("Foo");
    zombie1->Announce(); // zombie announces itself
    delete zombie1; // free the memory when done
    
    // zombie on the stack
    RandomChump("Hoo");

    return (0);
}
