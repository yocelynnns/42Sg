/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:25:06 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/10 14:34:09 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    std::cout << "=== Creating Original ClapTrap ===" << std::endl;
    ClapTrap original("OG");

    std::cout << "\n=== Copying ClapTrap ===" << std::endl;
    ClapTrap copy = original; // Calls ClapTrap copy constructor

    std::cout << "\n=== Modifying Original, Not Copy ===" << std::endl;
    original.attack("Dummy");
    original.takeDamage(4);
    original.beRepaired(6); // Should cap at 10 HP

    std::cout << "\n=== Check Copy Hasn't Changed ===" << std::endl;
    copy.attack("Still Dummy");

    std::cout << "\n=== Repair Beyond Max Test ===" << std::endl;
    ClapTrap healer("Medic");
    healer.takeDamage(5); // down to 5 HP
    healer.beRepaired(10); // should cap at 10 HP, not 15

    std::cout << "\n=== Before/After HP & Energy Test ===" << std::endl;
    ClapTrap stat("Stats");
    stat.takeDamage(3); // 7 HP
    stat.beRepaired(2); // 9 HP
    stat.attack("Target1"); // -1 energy
    stat.beRepaired(3); // 10 HP capped

    std::cout << "\n=== KO Test ===" << std::endl;
    ClapTrap ko("Die");
    ko.takeDamage(100); // Should die
    ko.attack("Ghost"); // Shouldn't be able to attack
    ko.beRepaired(10); // Shouldn't be able to repair

    std::cout << "\n=== Creating Original ScavTrap ===" << std::endl;
    ScavTrap scav1("SC4V");

    std::cout << "\n=== Copying ScavTrap ===" << std::endl;
    ScavTrap scav2 = scav1; // Calls ScavTrap copy constructor

    std::cout << "\n=== Assignment of ScavTrap ===" << std::endl;
    ScavTrap scav3;
    scav3 = scav1; // Calls ScavTrap assignment operator

    std::cout << "\n=== Using ScavTrap abilities ===" << std::endl;
    scav1.attack("Bandit");
    scav1.guardGate();

    std::cout << "\n=== ScavTrap Taking and Repairing Damage ===" << std::endl;
    scav1.takeDamage(90);
    scav1.beRepaired(100); // Should not go beyond 100
    scav1.attack("Skag");

    std::cout << "\n=== Destroying Objects in Reverse Order ===" << std::endl;
    return 0;
}


// #include "ClapTrap.hpp"
// #include "ScavTrap.hpp"

// int main() {
//     // Test Case 1: Basic Construction and Destruction
//     {
//         std::cout << "=== Creating ClapTrap ===" << std::endl;
//         ClapTrap claptrap("CLTP");
//     } // Check for destruction message

//     // Test Case 2: Attack with Sufficient Energy and Health
//     {
//         std::cout << "\n=== Normal Attack ===" << std::endl;
//         ClapTrap claptrap("CLTP");
//         claptrap.attack("target1"); // Expect attack message
//     }

//     // Test Case 3: Attack with Insufficient Energy
//     {
//         std::cout << "\n=== Attack with Insufficient Energy ===" << std::endl;
//         ClapTrap claptrap("CLTP");
//         claptrap.takeDamage(10); // Should die
//         claptrap.attack("target1"); // Expect dead message
//     }

//     // Test Case 4: Attack with Insufficient Health
//     {
//         std::cout << "\n=== Attack with Insufficient Health ===" << std::endl;
//         ClapTrap claptrap("CLTP");
//         claptrap.takeDamage(5);
//         claptrap.attack("target1"); // Expect dead message
//     }

//     // Test Case 5: Taking Damage
//     {
//         std::cout << "\n=== Taking Damage ===" << std::endl;
//         ClapTrap claptrap("CLTP");
//         claptrap.takeDamage(5); // Expect damage message
//         claptrap.takeDamage(5); // Expect death message
//     }

//     // Test Case 6: Repairing Health
//     {
//         std::cout << "\n=== Repairing Health ===" << std::endl;
//         ClapTrap claptrap("CLTP");
//         claptrap.takeDamage(5);
//         claptrap.beRepaired(3); // Expect repair message
//     }

//     // Test Case 7: Repairing When Dead
//     {
//         std::cout << "\n=== Repairing When Dead ===" << std::endl;
//         ClapTrap claptrap("CLTP");
//         claptrap.takeDamage(10); // Should die
//         claptrap.beRepaired(5); // Expect dead message
//     }

//     // Test Cases for ScavTrap

//     // Test Case 1: Basic Construction and Destruction
//     {
//         std::cout << "\n=== Creating ScavTrap ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//     } // Check for destruction message

//     // Test Case 2: Attack with Sufficient Energy and Health
//     {
//         std::cout << "\n=== ScavTrap Normal Attack ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//         scavtrap.attack("target2"); // Expect attack message
//     }

//     // Test Case 3: Attack with Insufficient Energy
//     {
//         std::cout << "\n=== ScavTrap Attack with Insufficient Energy ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//         scavtrap.takeDamage(100); // Should die
//         scavtrap.attack("target2"); // Expect dead message
//     }

//     // Test Case 4: Attack with Insufficient Health
//     {
//         std::cout << "\n=== ScavTrap Attack with Insufficient Health ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//         scavtrap.takeDamage(50);
//         scavtrap.attack("target2"); // Expect dead message
//     }

//     // Test Case 5: Taking Damage
//     {
//         std::cout << "\n=== ScavTrap Taking Damage ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//         scavtrap.takeDamage(50); // Expect damage message
//         scavtrap.takeDamage(60); // Expect death message
//     }

//     // Test Case 6: Repairing Health
//     {
//         std::cout << "\n=== ScavTrap Repairing Health ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//         scavtrap.takeDamage(50);
//         scavtrap.beRepaired(20); // Expect repair message
//     }

//     // Test Case 7: Repairing When Dead
//     {
//         std::cout << "\n=== ScavTrap Repairing When Dead ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//         scavtrap.takeDamage(100); // Should die
//         scavtrap.beRepaired(10); // Expect dead message
//     }

//     // Test Case 8: Guard Gate Functionality
//     {
//         std::cout << "\n=== ScavTrap Guard Gate ===" << std::endl;
//         ScavTrap scavtrap("SCVT");
//         scavtrap.guardGate(); // Expect guard gate message
//     }

//     return 0;
// }
