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

#include "PIVO_Dep.hpp"
#include "PIVO_Widget.hpp"
#include "PIVO_Vector.hpp"
#include "PIVO_Math.hpp"

struct SDL_Renderer;

namespace pivo{
class Line : public Widget{
struct Points{
    Vector2D a{0, 0};
    Vector2D b{0, 0};
};
public:
    void setPoints(Vector2D& a, Vector2D& b);

    Points getPoints() const;

    virtual bool containsPoint(const Vector2D& point) const override;
private:
    Points _points;

    virtual void _draw(SDL_Renderer* __renderer) override;

    virtual Vector2D _computePivotOffset() const override;
};
}