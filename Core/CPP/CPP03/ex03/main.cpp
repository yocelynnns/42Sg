/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:25:24 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/10 16:39:28 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main() {
    std::cout << "========== Test 1: Construction & whoAmI ==========\n";
    DiamondTrap d1("Ruby");
    d1.whoAmI();  // Should show Ruby and Ruby_clap_name

    std::cout << "\n========== Test 2: Attribute Inheritance Check ==========\n";
    std::cout << "Expected: HP = 100 (Frag), Energy = 50 (Scav), AttackDmg = 30 (Frag)\n";
    std::cout << "Actual -> HP: " << d1.getHP()
              << " | Energy: " << d1.getEnergy()
              << " | Damage: " << d1.getDamage() << std::endl;

    std::cout << "\n========== Test 3: Attack, Damage, Repair ==========\n";
    d1.attack("TargetBot");
    d1.takeDamage(20);
    d1.beRepaired(15);
    std::cout << "After actions -> HP: " << d1.getHP()
              << " | Energy: " << d1.getEnergy() << std::endl;

    std::cout << "\n========== Test 4: Copy Constructor ==========\n";
    DiamondTrap d2(d1);
    d2.whoAmI();
    std::cout << "Copy -> HP: " << d2.getHP()
              << " | Energy: " << d2.getEnergy()
              << " | Damage: " << d2.getDamage() << std::endl;

    std::cout << "\n========== Test 5: Assignment Operator ==========\n";
    DiamondTrap d3;
    d3 = d1;
    d3.whoAmI();

    std::cout << "\n========== Test 6: Max HP Capping ==========\n";
    d3.beRepaired(999);  // Should cap at 100
    std::cout << "After big heal -> HP: " << d3.getHP() << std::endl;

    std::cout << "\n========== Test 7: Energy Exhaustion ==========\n";
    for (int i = 0; i < 55; ++i)
        d3.attack("BotOverload");  // Should fail after 50 energy

    std::cout << "\n========== Test 8: Death Check ==========\n";
    d3.takeDamage(999);  // Bring HP to 0
    d3.attack("NoOne");  // Should not attack
    d3.beRepaired(20);   // Should not repair

    std::cout << "\n========== End of DiamondTrap Tests ==========\n";
    return 0;
}

// int main() {
//     std::cout << "----- Creating DiamondTrap -----" << std::endl;
//     DiamondTrap dt("Diamondy");

//     std::cout << "\n----- Testing attack() -----" << std::endl;
//     dt.attack("TargetDummy");

//     std::cout << "\n----- Testing repair() -----" << std::endl;
//     dt.beRepaired(30);

//     std::cout << "\n----- Testing takeDamage() -----" << std::endl;
//     dt.takeDamage(40);

//     std::cout << "\n----- Testing special abilities -----" << std::endl;
//     dt.guardGate();        // From ScavTrap
//     dt.highFivesGuys();    // From FragTrap
//     dt.whoAmI();           // DiamondTrap's own

//     std::cout << "\n----- End of main (destructors will be called) -----" << std::endl;

//     return 0;
// }
