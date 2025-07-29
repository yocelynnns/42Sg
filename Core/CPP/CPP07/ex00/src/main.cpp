/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:56:20 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/07/23 13:19:23 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

int main( void )
{
    int a = 2;
    int b = 3;
    
    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
    
    std::string c = "chaine1";
    std::string d = "chaine2";
    
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
    
    // ------Cant compile!
    // int e = 6;
    // std::string f = "3";
    // ::swap(e, f);
    
    return 0;
}

// int main() {
//     {
//         std::cout << "---- INT TEST ----" << std::endl;
//         int a = 10;
//         int b = 20;
//         std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
//         swap(a, b);
//         std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
//         std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
//         std::cout << "max(a, b) = " << ::max(a, b) << std::endl;
//     }

//     {
//         std::cout << "\n---- STRING TEST ----" << std::endl;
//         std::string c = "apple";
//         std::string d = "banana";
//         std::cout << "Before swap: c = " << c << ", d = " << d << std::endl;
//         swap(c, d);
//         std::cout << "After swap: c = " << c << ", d = " << d << std::endl;
//         std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
//         std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
//     }

//     {
//         std::cout << "\n---- FLOAT TEST ----" << std::endl;
//         float x = 20.5f;
//         float y = 42.5f;
//         std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
//         swap(x, y);
//         std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
//         std::cout << "min(x, y) = " << ::min(x, y) << std::endl;
//         std::cout << "max(x, y) = " << ::max(x, y) << std::endl;
//     }

//     {
//         std::cout << "\n---- CHAR TEST ----" << std::endl;
//         char w = 'W';
//         char z = 'Z';
//         std::cout << "Before swap: w = " << w << ", z = " << z << std::endl;
//         swap(w, z);
//         std::cout << "After swap: w = " << w << ", z = " << z << std::endl;
//         std::cout << "min(w, z) = " << ::min(w, z) << std::endl;
//         std::cout << "max(w, z) = " << ::max(w, z) << std::endl;
//     }

//     return 0;
// }
