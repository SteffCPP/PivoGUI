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

#include "PIVO_Vector.hpp"
#include "PIVO_Color.hpp"
#include "PIVO_Widget.hpp"
#include "PIVO_Dep.hpp"

struct SDL_Renderer;

namespace pivo{
class Ellipse : 
    public Widget,
    public texturable,
    public sizeable,
    public rotatable,
    public borderable,
    public pivotable,
    public positionable{
public:
    Ellipse();
    Ellipse(const Vector2D& size,
            const Vector2D& pos,
            const Color_RGBA& color=colors::Red);

    bool containsPoint(const Vector2D& point) const override;
private:
    void _draw(SDL_Renderer* __renderer) override;
    Vector2D _computePivotOffset() const override;
};
}
