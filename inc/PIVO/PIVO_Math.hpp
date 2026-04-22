/*
PivoGUI
Copyright (c) 2026 Stefano Rando (randostefano39@proton.me)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required. 
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#pragma once

#include <random>
#include <cmath>

namespace pivo{
	namespace math{
		/// Mathematical constant PI.
		constexpr double PI = 3.1415926535897932384626;

		/// Converts degrees to radians.
		/// @param __deg Angle in degrees.
		/// @return Equivalent angle in radians.
		constexpr double degToRad(const double __deg) {
			return __deg * (PI / 180);
		}

		/// Converts radians to degrees.
		/// @param __rad Angle in radians.
		/// @return Equivalent angle in degrees.
		constexpr double radToDeg(const double __rad) {
			return __rad * (180 / PI);
		}

		template<std::integral T>
		const T generateRandNum(const T a,const T b){
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::uniform_int_distribution<T> dis(a, b);
			return dis(gen);
		}
	}
}