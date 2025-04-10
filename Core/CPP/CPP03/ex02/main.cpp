/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:51:32 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/10 15:44:51 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "=== Creating FragTrap ===" << std::endl;
    FragTrap frag1("FR4G");

    std::cout << "\n=== Copy Constructing FragTrap ===" << std::endl;
    FragTrap frag2 = frag1;

    std::cout << "\n=== Assigning FragTrap ===" << std::endl;
    FragTrap frag3;
    frag3 = frag1;

    std::cout << "\n=== Using FragTrap Abilities ===" << std::endl;
    frag1.attack("Mutant Skag");
    frag1.takeDamage(40);
    frag1.beRepaired(20);
    frag1.highFivesGuys();

    std::cout << "\n=== Testing FragTrap Repair Cap ===" << std::endl;
    frag1.takeDamage(90);      // Should reduce to 0 HP
    frag1.beRepaired(50);      // Should not work (dead)
    frag1.attack("No One");    // Should not work (dead)

    std::cout << "\n=== Creating Default FragTrap ===" << std::endl;
    FragTrap defaultFrag;

    std::cout << "\n=== Special High Five on Default ===" << std::endl;
    defaultFrag.highFivesGuys();

    std::cout << "\n=== Destruction Begins ===" << std::endl;
    return 0;
}

// int main() {
//     std::cout << "\n=== Test 1: Constructor/Destructor ===" << std::endl;
//     {
//         ClapTrap a("CL4P-TP");
//         ScavTrap b("SC4V-TP");
//         FragTrap c("FR4G-TP");
//     }

//     std::cout << "\n=== Test 2: Valid Attack ===" << std::endl;
//     {
//         FragTrap frag("FRAG");
//         frag.attack("enemy");
//     }

//     std::cout << "\n=== Test 3: Attack with 0 Energy ===" << std::endl;
//     {
//         ClapTrap bot("ZeroEnergy");
//         for (int i = 0; i < 10; ++i)
//             bot.attack("target");
//         bot.attack("target"); // should fail
//     }

//     std::cout << "\n=== Test 4: Attack While Dead ===" << std::endl;
//     {
//         ScavTrap scav("DeadBot");
//         scav.takeDamage(200);
//         scav.attack("target");
//     }

//     std::cout << "\n=== Test 5: Take Damage and Die ===" << std::endl;
//     {
//         ClapTrap bot("Tanky");
//         bot.takeDamage(5);
//         bot.takeDamage(6); // should die here
//     }

//     std::cout << "\n=== Test 6: Be Repaired ===" << std::endl;
//     {
//         ClapTrap bot("Fixer");
//         bot.takeDamage(3);
//         bot.beRepaired(5);
//     }

//     std::cout << "\n=== Test 7: Be Repaired With 0 Energy ===" << std::endl;
//     {
//         ClapTrap bot("LowBattery");
//         for (int i = 0; i < 10; ++i)
//             bot.attack("dummy"); // drain energy
//         bot.beRepaired(5); // should fail
//     }

//     std::cout << "\n=== Test 8: Repair When Dead ===" << std::endl;
//     {
//         FragTrap frag("RipFrag");
//         frag.takeDamage(150);
//         frag.beRepaired(30); // should fail
//     }

//     std::cout << "\n=== Test 9: Special Abilities ===" << std::endl;
//     {
//         ScavTrap scav("GuardBot");
//         scav.guardGate();

//         FragTrap frag("HighFiveBot");
//         frag.highFivesGuys();
//     }

//     std::cout << "\n=== Test 10: Combat Simulation ===" << std::endl;
//     {
//         ScavTrap scav("Scavy");
//         FragTrap frag("Fraggy");

//         scav.attack("Fraggy");
//         frag.takeDamage(20);

//         frag.attack("Scavy");
//         scav.takeDamage(30);

//         scav.guardGate();
//         frag.highFivesGuys();
//     }

//     return 0;
// }
