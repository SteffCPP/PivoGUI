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

#include "Shapes/PIVO_Triangle.hpp"
#include "../PIVO_SDL.cpp"

namespace pivo{
Triangle::Triangle(const Vector2D& a,
             const Vector2D& b,
             const Vector2D& c,
             const Color_RGBA& color)
{
    setPoints(a, b, c);
    _color = color;
}
Triangle::Triangle(){}

void Triangle::setPoints(const Vector2D& a,
                const Vector2D& b,
                const Vector2D& c)
{   
    _a = a;
    _b = b;
    _c = c;
}

bool Triangle::containsPoint(const Vector2D& p) const {
    auto sign = [](Vector2D p1, Vector2D p2, Vector2D p3){
        return (p1.x - p3.x)*(p2.y - p3.y) -
               (p2.x - p3.x)*(p1.y - p3.y);
    };

    float d1 = sign(p, _a, _b);
    float d2 = sign(p, _b, _c);
    float d3 = sign(p, _c, _a);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void Triangle::_draw(SDL_Renderer* __renderer){
    if(_hide) return;
    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

    SDL_FColor col = {
        _color.r / 255.0f,
        _color.g / 255.0f,
        _color.b / 255.0f,
        _color.a / 255.0f
    };

    Vector2D offset = _pos + _computePivotOffset();

    SDL_Vertex v[3];

    v[0].position = {_a.x + offset.x, _a.y + offset.y};
    v[1].position = {_b.x + offset.x, _b.y + offset.y};
    v[2].position = {_c.x + offset.x, _c.y + offset.y};

    v[0].color = col;
    v[1].color = col;
    v[2].color = col;

    v[0].tex_coord = {0,0};
    v[1].tex_coord = {1,0};
    v[2].tex_coord = {0,1};

    SDL_Texture* tex = nullptr;

    if(_hasImage)
        tex = Texture_Manager::getSDLTexture(_img);
    

    SDL_RenderGeometry(__renderer, tex, v, 3, nullptr, 0);

    if(_borderWidth > 0){
        SDL_SetRenderDrawColor(__renderer,
            _borderColor.r,
            _borderColor.g,
            _borderColor.b,
            _borderColor.a
        );

        SDL_RenderLine(__renderer, v[0].position.x, v[0].position.y, v[1].position.x, v[1].position.y);
        SDL_RenderLine(__renderer, v[1].position.x, v[1].position.y, v[2].position.x, v[2].position.y);
        SDL_RenderLine(__renderer, v[2].position.x, v[2].position.y, v[0].position.x, v[0].position.y);
    }

    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
}
Vector2D Triangle::_computePivotOffset() const {
    switch(_pivot){
        case Pivot::TOP_LEFT:     return {0, 0};
        case Pivot::TOP:          return {-(std::min({_a.x,_b.x,_c.x}) + std::max({_a.x,_b.x,_c.x})) / 2, 0};
        case Pivot::CENTER:       return {-(_a.x+_b.x+_c.x ) / 3.0f,
                                         -(_a.y+_b.y+_c.y ) / 3.0f};

        default: return {0,0};
    }
}
}