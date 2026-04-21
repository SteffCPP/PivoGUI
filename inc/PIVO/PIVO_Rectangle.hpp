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

#include "PIVO_Widget.hpp"

struct SDL_Rect;

namespace pivo{
	class Rectangle : public Widget, public texturable {
public:
    /// Checks if a point is inside the rectangle.
    /// @param point Point in world coordinates.
    /// @return True if the point is inside the rectangle.
    virtual bool containsPoint(const Vector2D& point) const override;

    /// Constructs a Rectangle with size, position, colors and rotation.
    /// @param size Size of the rectangle (width, height).
    /// @param pos Position of the rectangle in world space.
    /// @param bgColor Background color (default = red).
    /// @param bdWidth Border thickness in pixels (default = 0).
    /// @param bdColor Border color (default = transparent).
    /// @param rotRad Rotation in radians (default = 0).
    Rectangle(const Vector2D& size,
              const Vector2D& pos,
              const Color_RGBA& bgColor = colors::Red,
              const float bdWidth = 0,
              const Color_RGBA& bdColor = colors::Transparent,
              const float rotRad = 0);

    /// Default constructor.
    Rectangle();

private:
    /// Internal render function for the rectangle.
    /// @param __renderer SDL rendering context.
    void _draw(SDL_Renderer* __renderer) override;
};
}