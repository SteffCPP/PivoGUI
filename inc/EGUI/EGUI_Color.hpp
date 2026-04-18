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
	struct Color_RGBA{
		std::uint8_t r{0}, g{0}, b{0}, a{255};
		
		Color_RGBA(const std::uint8_t R, const std::uint8_t G, const std::uint8_t B, const std::uint8_t A=255);
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