/*
EGUI - Embedded Graphics Utility Interface
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
#include <cstdint>
#include <algorithm>

namespace egui{
	class Color_RGBA{
	public:
		constexpr void setColors(const uint32_t R, const uint32_t G, const uint32_t B, const uint32_t A=255){ 
			_r = std::clamp(R, (uint32_t)0, (uint32_t)255);
			_g = std::clamp(G, (uint32_t)0, (uint32_t)255); 
			_b = std::clamp(B, (uint32_t)0, (uint32_t)255); 
			_a = std::clamp(A, (uint32_t)0, (uint32_t)255);
		}

		constexpr uint32_t R() const { return _r; }
		constexpr uint32_t G() const { return _g; }
		constexpr uint32_t B() const { return _b; }
		constexpr uint32_t A() const { return _a; }

		void setR(const uint32_t R){ _r = std::clamp(R, (uint32_t)0, (uint32_t)255); }
		void setG(const uint32_t G){ _g = std::clamp(G, (uint32_t)0, (uint32_t)255); }
		void setB(const uint32_t B){ _b = std::clamp(B, (uint32_t)0, (uint32_t)255); }
		void setA(const uint32_t A){ _a = std::clamp(A, (uint32_t)0, (uint32_t)255); }

		Color_RGBA(){}
		Color_RGBA(const uint32_t R, const uint32_t G, const uint32_t B, const uint32_t A=255){
			setColors(R, G, B, A);
		}
		~Color_RGBA(){};
	private:
		uint32_t _r{0}, _g{0}, _b{0}, _a{255};
	};

	namespace colors{
		extern Color_RGBA Red;
		extern Color_RGBA Green;
		extern Color_RGBA Blue;
		extern Color_RGBA Black;
		extern Color_RGBA White;
		extern Color_RGBA Yellow;
		extern Color_RGBA Cyan;
		extern Color_RGBA Magenta;
		extern Color_RGBA Gray;
		extern Color_RGBA Transparent;
	}
}