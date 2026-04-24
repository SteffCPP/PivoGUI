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

#include "PIVO/Shapes/PIVO_Ellipse.hpp"
#include "../PIVO_SDL.cpp"

#include <vector>

namespace pivo{
Ellipse::Ellipse(){}
Ellipse::Ellipse(const Vector2D& size,
                const Vector2D& pos,
                const Color_RGBA& color)
{
    _size = size;
    _pos = pos;
    _color = color;
}

bool Ellipse::containsPoint(const Vector2D& point) const {
    Vector2D topLeft = _pos + _computePivotOffset();
    Vector2D center = topLeft + Vector2D{_size.x/2.0f, _size.y/2.0f};

    float a = _size.x / 2.0f;
    float b = _size.y / 2.0f;
    

    float dx = point.x - center.x;
    float dy = point.y - center.y;

    return (dx*dx)/(a*a) + (dy*dy)/(b*b) <= 1.0f;
}

void Ellipse::_draw(SDL_Renderer* __renderer){
    if(_hide) return;
    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

    const int segments = std::max(32, (int)(_size.x+_size.y)/8);

    Vector2D topLeft = _pos + _computePivotOffset();
    Vector2D center = topLeft + Vector2D{_size.x/2.0f, _size.y/2.0f};

    float a = _size.x / 2.0f;
    float b = _size.y / 2.0f;

    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    vertices.reserve(segments + 2);
    indices.reserve(segments * 3);

    SDL_FColor col = {(float)_color.r, (float)_color.g, (float)_color.b, (float)_color.a};

    SDL_Vertex centerV;
    centerV.position = {center.x, center.y};
    centerV.color = col;
    centerV.tex_coord = {0.5f, 0.5f};

    vertices.push_back(centerV);

    for(int i = 0; i <= segments; i++){
        float t = (float)i / segments * 2.0f * M_PI;

        float x = center.x + a * cos(t);
        float y = center.y + b * sin(t);

        SDL_Vertex v;
        v.position = {x, y};
        v.color = col;

        v.tex_coord = {
            0.5f + (float)cos(t) * 0.5f,
            0.5f + (float)sin(t) * 0.5f
        };

        vertices.push_back(v);
    }

    for(int i=1; i<=segments; i++){
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    SDL_Texture* tex = nullptr;
    if(_hasTexture){
        tex = Texture_Manager::getSDLTexture(_texture);
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    }

    SDL_RenderGeometry(
        __renderer,
        tex,
        vertices.data(),
        (int)vertices.size(),
        indices.data(),
        (int)indices.size()
    );

    if(_borderWidth > 0){
        SDL_SetRenderDrawColor(
            __renderer,
            _borderColor.r,
            _borderColor.g,
            _borderColor.b,
            _borderColor.a
        );

        for(int i = 0; i <= segments; i++){
            float t1 = (float)i/segments * 2.0f * math::PI;
            float t2 = (float)(i + 1)/segments * 2.0f * math::PI;

            float x1 = center.x+a * cos(t1);
            float y1 = center.y+b * sin(t1);

            float x2 = center.x+a * cos(t2);
            float y2 = center.y+b * sin(t2);

            SDL_RenderLine(__renderer, x1, y1, x2, y2);
        }
    }

    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
}

Vector2D Ellipse::_computePivotOffset() const {
    switch(_pivot){
        case Pivot::TOP_LEFT:     return {0, 0};
        case Pivot::TOP:          return {-_size.x/2, 0};
        case Pivot::TOP_RIGHT:    return {-_size.x, 0};

        case Pivot::LEFT:         return {0, -_size.y/2};
        case Pivot::CENTER:       return {-_size.x/2, -_size.y/2};
        case Pivot::RIGHT:        return {-_size.x, -_size.y/2};

        case Pivot::BOTTOM_LEFT:  return {0, -_size.y};
        case Pivot::BOTTOM:       return {-_size.x/2, -_size.y};
        case Pivot::BOTTOM_RIGHT: return {-_size.x, -_size.y};
    }
    return {0,0};
}
}