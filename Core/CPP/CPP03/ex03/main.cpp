/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:25:24 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/05 22:58:23 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main() {
    std::cout << "----- Creating DiamondTrap -----" << std::endl;
    DiamondTrap dt("Diamondy");

    std::cout << "\n----- Testing attack() -----" << std::endl;
    dt.attack("TargetDummy");

    std::cout << "\n----- Testing repair() -----" << std::endl;
    dt.beRepaired(30);

    std::cout << "\n----- Testing takeDamage() -----" << std::endl;
    dt.takeDamage(40);

    std::cout << "\n----- Testing special abilities -----" << std::endl;
    dt.guardGate();        // From ScavTrap
    dt.highFivesGuys();    // From FragTrap
    dt.whoAmI();           // DiamondTrap's own

    std::cout << "\n----- End of main (destructors will be called) -----" << std::endl;

    return 0;
}
