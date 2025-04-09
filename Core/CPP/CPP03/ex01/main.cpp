/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:25:06 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/05 20:48:18 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    // Test Case 1: Basic Construction and Destruction
    {
        std::cout << "=== Creating ClapTrap ===" << std::endl;
        ClapTrap claptrap("CLTP");
    } // Check for destruction message

    // Test Case 2: Attack with Sufficient Energy and Health
    {
        std::cout << "\n=== Normal Attack ===" << std::endl;
        ClapTrap claptrap("CLTP");
        claptrap.attack("target1"); // Expect attack message
    }

    // Test Case 3: Attack with Insufficient Energy
    {
        std::cout << "\n=== Attack with Insufficient Energy ===" << std::endl;
        ClapTrap claptrap("CLTP");
        claptrap.takeDamage(10); // Should die
        claptrap.attack("target1"); // Expect dead message
    }

    // Test Case 4: Attack with Insufficient Health
    {
        std::cout << "\n=== Attack with Insufficient Health ===" << std::endl;
        ClapTrap claptrap("CLTP");
        claptrap.takeDamage(5);
        claptrap.attack("target1"); // Expect dead message
    }

    // Test Case 5: Taking Damage
    {
        std::cout << "\n=== Taking Damage ===" << std::endl;
        ClapTrap claptrap("CLTP");
        claptrap.takeDamage(5); // Expect damage message
        claptrap.takeDamage(5); // Expect death message
    }

    // Test Case 6: Repairing Health
    {
        std::cout << "\n=== Repairing Health ===" << std::endl;
        ClapTrap claptrap("CLTP");
        claptrap.takeDamage(5);
        claptrap.beRepaired(3); // Expect repair message
    }

    // Test Case 7: Repairing When Dead
    {
        std::cout << "\n=== Repairing When Dead ===" << std::endl;
        ClapTrap claptrap("CLTP");
        claptrap.takeDamage(10); // Should die
        claptrap.beRepaired(5); // Expect dead message
    }

    // Test Cases for ScavTrap

    // Test Case 1: Basic Construction and Destruction
    {
        std::cout << "\n=== Creating ScavTrap ===" << std::endl;
        ScavTrap scavtrap("SCVT");
    } // Check for destruction message

    // Test Case 2: Attack with Sufficient Energy and Health
    {
        std::cout << "\n=== ScavTrap Normal Attack ===" << std::endl;
        ScavTrap scavtrap("SCVT");
        scavtrap.attack("target2"); // Expect attack message
    }

    // Test Case 3: Attack with Insufficient Energy
    {
        std::cout << "\n=== ScavTrap Attack with Insufficient Energy ===" << std::endl;
        ScavTrap scavtrap("SCVT");
        scavtrap.takeDamage(100); // Should die
        scavtrap.attack("target2"); // Expect dead message
    }

    // Test Case 4: Attack with Insufficient Health
    {
        std::cout << "\n=== ScavTrap Attack with Insufficient Health ===" << std::endl;
        ScavTrap scavtrap("SCVT");
        scavtrap.takeDamage(50);
        scavtrap.attack("target2"); // Expect dead message
    }

    // Test Case 5: Taking Damage
    {
        std::cout << "\n=== ScavTrap Taking Damage ===" << std::endl;
        ScavTrap scavtrap("SCVT");
        scavtrap.takeDamage(50); // Expect damage message
        scavtrap.takeDamage(60); // Expect death message
    }

    // Test Case 6: Repairing Health
    {
        std::cout << "\n=== ScavTrap Repairing Health ===" << std::endl;
        ScavTrap scavtrap("SCVT");
        scavtrap.takeDamage(50);
        scavtrap.beRepaired(20); // Expect repair message
    }

    // Test Case 7: Repairing When Dead
    {
        std::cout << "\n=== ScavTrap Repairing When Dead ===" << std::endl;
        ScavTrap scavtrap("SCVT");
        scavtrap.takeDamage(100); // Should die
        scavtrap.beRepaired(10); // Expect dead message
    }

    // Test Case 8: Guard Gate Functionality
    {
        std::cout << "\n=== ScavTrap Guard Gate ===" << std::endl;
        ScavTrap scavtrap("SCVT");
        scavtrap.guardGate(); // Expect guard gate message
    }

    return 0;
}
