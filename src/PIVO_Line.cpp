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

#include "PIVO_Line.hpp"
#include "PIVO_SDL.cpp"

namespace pivo{
void Line::setPoints(Vector2D& a, Vector2D& b){ _points = {a, b}; }
Line::Points Line::getPoints() const { return _points; }
bool Line::containsPoint(const Vector2D& point) const {
    int x1 = _points.a.x;
    int y1 = _points.a.y;

    int x2 = _points.b.x;
    int y2 = _points.b.y;

    int x0 = point.x;
    int y0 = point.y;

    int distance = std::abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1)/std::sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
    return distance == 0;
}

Line::Line(){}
Line::Line(const Vector2D pointA, const Vector2D pointB, Color_RGBA color){
    _points.a = pointA;
    _points.b = pointB;
    _color = color;
}

void Line::_draw(SDL_Renderer* __renderer){
    if(_hide) return;
    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(
		__renderer,
		_color.r,
		_color.g,
		_color.b,
		_color.a
    );
    SDL_RenderLine(__renderer, _points.a.x, _points.a.y, _points.b.x, _points.b.y);

    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
}
}