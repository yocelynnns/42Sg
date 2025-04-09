/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:45:50 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/05 17:14:30 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main() {
    std::cout << "=== Creating ClapTrap ===" << std::endl;
    ClapTrap ct("Clappy");

    std::cout << "\n=== Normal Attack ===" << std::endl;
    ct.attack("TargetBot");

    std::cout << "\n=== Repairing (should work) ===" << std::endl;
    ct.beRepaired(5);

    std::cout << "\n=== Taking Damage (non-fatal) ===" << std::endl;
    ct.takeDamage(3);

    std::cout << "\n=== Taking Damage (fatal) ===" << std::endl;
    ct.takeDamage(20); // Should kill the ClapTrap

    std::cout << "\n=== Trying to Attack After Death ===" << std::endl;
    ct.attack("TargetBot");

    std::cout << "\n=== Trying to Repair After Death ===" << std::endl;
    ct.beRepaired(5);

    std::cout << "\n=== Creating New ClapTrap for Energy Tests ===" << std::endl;
    ClapTrap tiredBot("TiredBot");

    std::cout << "\n=== Depleting All Energy with Attacks ===" << std::endl;
    for (int i = 0; i < 10; i++) {
        tiredBot.attack("DummyBot");
    }

    std::cout << "\n=== Trying to Attack With No Energy ===" << std::endl;
    tiredBot.attack("DummyBot");

    std::cout << "\n=== Trying to Repair With No Energy ===" << std::endl;
    tiredBot.beRepaired(5);

    std::cout << "\n=== Creating Another ClapTrap to Take Damage ===" << std::endl;
    ClapTrap punchingBag("PunchingBag");

    punchingBag.takeDamage(5);
    punchingBag.takeDamage(3);
    punchingBag.takeDamage(2); // Brings health to 0

    punchingBag.takeDamage(1); // Already dead
    punchingBag.beRepaired(3); // Should not repair because it's dead

    std::cout << "\n=== End of Test ===" << std::endl;
    return 0;
}
