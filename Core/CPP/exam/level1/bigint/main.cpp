/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:14:11 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/24 16:03:37 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

int main() {
    BigInt a("111111111111111111111");
    BigInt b("222222222222222222229");

    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;

    a += b;
    std::cout << "After a += b, a = " << a << std::endl;

    BigInt c("000000");
    std::cout << "c (from \"000000\") = " << c << std::endl;

    BigInt d("999");
    std::cout << "d++ = " << d++ << ", now d = " << d << std::endl;
    std::cout << "++d = " << ++d << std::endl;

    BigInt e = a << 2;
    std::cout << "a << 2 = " << e << std::endl;

    BigInt f = e >> 2;
    std::cout << "e >> 2 = " << f << std::endl;

    std::cout << "a == b? " << (a == b) << std::endl;
    std::cout << "a > b? " << (a > b) << std::endl;
}


// int main() {
//     BigInt a("1");
//     BigInt b("22222");

//     std::cout << "a = " << a << ", b = " << b << std::endl;
//     std::cout << "a + b = " << (a + b) << std::endl;

//     a += b;
//     std::cout << "After a += b, a = " << a << std::endl;

//     BigInt c("000000");
//     std::cout << "c (from \"000000\") = " << c << std::endl;

//     BigInt d("999");
//     std::cout << "d++ = " << d++ << ", now d = " << d << std::endl;
//     std::cout << "++d = " << ++d << std::endl;

//     BigInt e("12345");   
//     e = e << 2;  // assign result back
//     std::cout << "e << 2 = " << e << std::endl;

//     BigInt f("12345");
//     f = f >> 2;  // assign result back
//     std::cout << "f >> 2 = " << f << std::endl;

//     std::cout << "a == b? " << (a == b) << std::endl;
//     std::cout << "a > b? " << (a > b) << std::endl;
// }
