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
#include <cstdint>
#include <algorithm>

namespace pivo{
	struct Color_RGBA {
    std::uint8_t r{0};
    std::uint8_t g{0};
    std::uint8_t b{0};
    std::uint8_t a{255};

    /// Constructs a color using RGBA components.
    /// @param R Red channel value [0 - 255].
    /// @param G Green channel value [0 - 255].
    /// @param B Blue channel value [0 - 255].
    /// @param A Alpha channel value [0 - 255] (default = 255 opaque).
    Color_RGBA(const std::uint8_t R,
               const std::uint8_t G,
               const std::uint8_t B,
               const std::uint8_t A = 255);
};

/// Predefined common colors.
namespace colors {
    extern Color_RGBA Red;        ///< Pure red color (255, 0, 0, 255)
    extern Color_RGBA Green;      ///< Pure green color (0, 255, 0, 255)
    extern Color_RGBA Blue;       ///< Pure blue color (0, 0, 255, 255)
    extern Color_RGBA Black;      ///< Black color (0, 0, 0, 255)
    extern Color_RGBA White;      ///< White color (255, 255, 255, 255)
    extern Color_RGBA Yellow;     ///< Yellow color (255, 255, 0, 255)
    extern Color_RGBA Cyan;       ///< Cyan color (0, 255, 255, 255)
    extern Color_RGBA Magenta;    ///< Magenta color (255, 0, 255, 255)
    extern Color_RGBA Gray;       ///< Gray color (128, 128, 128, 255)
    extern Color_RGBA Transparent;///< Fully transparent color (0, 0, 0, 0)
}
}