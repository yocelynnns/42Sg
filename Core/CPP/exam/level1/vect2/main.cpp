/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:14:11 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/06/26 14:39:59 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

#include "vect2.hpp"

void section(const std::string& title) {
	std::cout << "\n=== " << title << " ===\n";
}

int main() {
	section("Default Constructor");
	Vec2 a;
	std::cout << "a = " << a << std::endl;

	section("Custom Constructor");
	Vec2 b(3, 4);
	std::cout << "b = " << b << std::endl;

	section("Copy Constructor");
	Vec2 c(b);
	std::cout << "c = " << c << std::endl;

	section("Assignment Operator");
	Vec2 d;
	d = b;
	std::cout << "d = " << d << std::endl;

	section("Index Access");
	std::cout << "b[0] = " << b[0] << ", b[1] = " << b[1] << std::endl;

	section("Arithmetic Operators (+, -, *, /)");
	Vec2 e = a + b;
	std::cout << "a + b = " << e << std::endl;
	Vec2 f = b - Vec2(1, 1);
	std::cout << "b - (1,1) = " << f << std::endl;
	Vec2 g = b * 2;
	std::cout << "b * 2 = " << g << std::endl;
	Vec2 h = 3 * b;
	std::cout << "3 * b = " << h << std::endl;
	Vec2 i = b / 2;
	std::cout << "b / 2 = " << i << std::endl;

	section("Compound Assignment Operators (+=, -=, *=)");
	Vec2 j(1, 1);
	j += Vec2(2, 2);
	std::cout << "j += (2,2) => " << j << std::endl;
	j -= Vec2(1, 1);
	std::cout << "j -= (1,1) => " << j << std::endl;
	j *= 2;
	std::cout << "j *= 2 => " << j << std::endl;

	section("Increment / Decrement");
	Vec2 k(5, 5);
	std::cout << "k = " << k << std::endl;
	std::cout << "k++ = " << k++ << std::endl;
	std::cout << "after k++: " << k << std::endl;
	std::cout << "++k = " << ++k << std::endl;
	std::cout << "k-- = " << k-- << std::endl;
	std::cout << "after k--: " << k << std::endl;
	std::cout << "--k = " << --k << std::endl;

	section("Equality and Inequality");
	Vec2 l(1, 2);
	Vec2 m(1, 2);
	Vec2 n(3, 4);
	std::cout << "l == m: " << (l == m) << std::endl; // 1
	std::cout << "l != n: " << (l != n) << std::endl; // 1

	section("Chained Operations");
	Vec2 result = l + m + n;
	std::cout << "l + m + n = " << result << std::endl;
    Vec2 result2 = l + m - n;
	std::cout << "l + m - n = " << result2 << std::endl;
    Vec2 result3 = l + m - n * 2;
	std::cout << "l + m - n * 2 = " << result3 << std::endl;
    Vec2 result4 = 2 * l + m - n;
	std::cout << "2 * l + m - n = " << result4 << std::endl;

	section("Self-assignment");
	Vec2 o(9, 9);
	o = o;
	std::cout << "o = o => " << o << std::endl;

	section("Const Vec2");
	const Vec2 p(10, 11);
	std::cout << "p = " << p << std::endl;
	std::cout << "p[0] = " << p[0] << ", p[1] = " << p[1] << std::endl;
	std::cout << "-p = " << -p << std::endl;
	// section("Out-of-Bounds Access");
	// std::cout << "Accessing p[2]..." << std::endl;
	// std::cout << p[2] << std::endl;
    // std::cout << "Accessing p[-1]..." << std::endl;
	// std::cout << p[-1] << std::endl;

	return 0;
}


// int main() {
//     std::cout << "== Default constructor ==" << std::endl;
//     Vec2 def;
//     std::cout << def << std::endl; // {0,0}

//     std::cout << "\n== Custom constructor ==" << std::endl;
//     Vec2 a(2, 3);
//     std::cout << a << std::endl; // {2,3}

//     std::cout << "\n== Copy constructor ==" << std::endl;
//     Vec2 b(a);
//     std::cout << b << std::endl; // {2,3}

//     std::cout << "\n== Assignment operator ==" << std::endl;
//     Vec2 c;
//     c = a;
//     std::cout << c << std::endl; // {2,3}

//     std::cout << "\n== operator+= ==" << std::endl;
//     c += Vec2(1, 1);
//     std::cout << c << std::endl; // {3,4}

//     std::cout << "\n== operator-= ==" << std::endl;
//     c -= Vec2(2, 1);
//     std::cout << c << std::endl; // {1,3}

//     std::cout << "\n== operator*= ==" << std::endl;
//     c *= 2;
//     std::cout << c << std::endl; // {2,6}

//     std::cout << "\n== operator+ ==" << std::endl;
//     Vec2 d = a + Vec2(4, 5);
//     std::cout << d << std::endl; // {6,8}

//     std::cout << "\n== operator- ==" << std::endl;
//     Vec2 e = a - Vec2(1, 1);
//     std::cout << e << std::endl; // {1,2}

//     std::cout << "\n== operator* (vector * scalar) ==" << std::endl;
//     Vec2 f = a * 3;
//     std::cout << f << std::endl; // {6,9}

//     std::cout << "\n== operator* (scalar * vector) ==" << std::endl;
//     Vec2 g = 3 * a;
//     std::cout << g << std::endl; // {6,9}

//     std::cout << "\n== operator/ ==" << std::endl;
//     Vec2 h = f / 3;
//     std::cout << h << std::endl; // {2,3}

//     std::cout << "\n== operator== and != ==" << std::endl;
//     std::cout << (a == h) << std::endl;  // 1 (true)
//     std::cout << (a != h) << std::endl;  // 0 (false)
//     std::cout << (a != c) << std::endl;  // 1 (true)

//     return 0;
// }
