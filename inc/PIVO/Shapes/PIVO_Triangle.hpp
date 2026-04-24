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

#include "PIVO/PIVO_Dep.hpp"
#include "PIVO/PIVO_Widget.hpp"

namespace pivo{
class Triangle : 
    public Widget,
    public texturable,
    public rotatable, 
    public borderable, 
    public pivotable, 
    public positionable{
public:
    Triangle(const Vector2D& a,
             const Vector2D& b,
             const Vector2D& c,
             const Color_RGBA& color = colors::Red);
    Triangle();

    void setPoints(const Vector2D& a,
                   const Vector2D& b,
                   const Vector2D& c);

    bool containsPoint(const Vector2D& point) const override;
private:
    void _draw(SDL_Renderer* __renderer) override;
    Vector2D _computePivotOffset() const override;

    Vector2D _a{0, 0}, _b{0, 0}, _c{0, 0};
};
}