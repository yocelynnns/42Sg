/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:53:09 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/05/28 14:14:47 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include "ICharacter.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;

    return 0;
}

// int main() {
//     std::cout << "\n========== Test 1: Equip More Than 4 Materia ==========\n";
//     Character test("Tester");
//     for (int i = 0; i < 6; ++i) {
//         if (i % 2 == 0)
//             test.equip(new Ice());
//         else
//             test.equip(new Cure());
//     }
//     for (int i = 0; i < 6; ++i)
//         test.use(i, test); // Only first 4 should show output

//     std::cout << "\n========== Test 2: Unequip Without Delete ==========\n";
//     Character me("me");
//     AMateria* ice = new Ice();
//     me.equip(ice);
//     me.unequip(0);
//     ice->use(me); // Should still work
//     delete ice; // Manual deletion

//     std::cout << "\n========== Test 3: Clone Independence ==========\n";
//     AMateria* original = new Cure();
//     AMateria* clone = original->clone();
//     delete original;
//     Character dummy("Dummy");
//     clone->use(dummy); // Should still print
//     delete clone;

//     std::cout << "\n========== Test 4: Learn More Than 4 Materia ==========\n";
//     MateriaSource src;
//     src.learnMateria(new Ice());
//     src.learnMateria(new Cure());
//     src.learnMateria(new Ice());
//     src.learnMateria(new Cure());
//     src.learnMateria(new Ice()); // Should be ignored

//     AMateria* m = src.createMateria("ice");
//     if (m) m->use(test);
//     delete m;

//     std::cout << "\n========== Test 5: Unknown Materia Request ==========\n";
//     AMateria* fire = src.createMateria("fire");
//     if (!fire)
//         std::cout << "Unknown materia not created (✅)" << std::endl;

//     std::cout << "\n========== Test 6: Use Invalid Index ==========\n";
//     Character hero("Hero");
//     hero.use(-1, hero); // Invalid index
//     hero.use(10, hero); // Invalid index
//     hero.equip(new Cure());
//     hero.use(0, hero); // Valid use

//     std::cout << "\n========== Test 7: Character Deep Copy ==========\n";
//     Character alice("Alice");
//     alice.equip(new Ice());
//     alice.equip(new Cure());

//     Character bob = alice; // Copy constructor
//     alice.use(0, bob); // Ice from Alice
//     bob.use(1, alice); // Cure from Bob

//     return 0;
// }

