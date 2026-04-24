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
    if(_hide||!__renderer)return;

    SDL_SetRenderDrawBlendMode(__renderer,SDL_BLENDMODE_BLEND);

    const int segments=std::max(32,(int)(_size.x+_size.y)/8);

    Vector2D topLeft=_pos+_computePivotOffset();
    Vector2D center=topLeft+Vector2D{_size.x/2.0f,_size.y/2.0f};

    float a=_size.x/2.0f;
    float b=_size.y/2.0f;

    SDL_Texture* tex=nullptr;

    if(_hasAnim&&_currAnim){
        Texture t=_currAnim->getCurrentFrame();
        tex=Texture_Manager::getSDLTexture(t);
    }else if(_hasTexture){
        tex=Texture_Manager::getSDLTexture(_texture);
    }

    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    SDL_Vertex centerV{};
    centerV.position={center.x,center.y};

    if(tex){
        centerV.color={1.0f,1.0f,1.0f,1.0f};
        centerV.tex_coord={0.5f,0.5f};
    }else{
        centerV.color={
            _color.r/255.0f,
            _color.g/255.0f,
            _color.b/255.0f,
            _color.a/255.0f
        };
        centerV.tex_coord={0,0};
    }

    vertices.push_back(centerV);

    for(int i=0;i<=segments;i++){
        float t=(float)i/segments*2.0f*M_PI;

        float cosT=cos(t);
        float sinT=sin(t);

        float x=center.x+a*cosT;
        float y=center.y+b*sinT;

        SDL_Vertex v{};
        v.position={x,y};

        if(tex){
            v.color={1.0f,1.0f,1.0f,1.0f};
            v.tex_coord={
                0.5f+cosT*0.5f,
                0.5f+sinT*0.5f
            };
        }else{
            v.color={
                _color.r/255.0f,
                _color.g/255.0f,
                _color.b/255.0f,
                _color.a/255.0f
            };
            v.tex_coord={0,0};
        }

        vertices.push_back(v);
    }

    for(int i=1;i<=segments;i++){
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i+1);
    }

    SDL_RenderGeometry(__renderer,tex,vertices.data(),(int)vertices.size(),indices.data(),(int)indices.size());

    if(_borderWidth>0){
        float innerA=a-_borderWidth;
        float innerB=b-_borderWidth;

        if(innerA<0)innerA=0;
        if(innerB<0)innerB=0;

        std::vector<SDL_Vertex> bVertices;
        std::vector<int> bIndices;

        for(int i=0;i<=segments;i++){
            float t=(float)i/segments*2.0f*M_PI;

            float cosT=cos(t);
            float sinT=sin(t);

            SDL_Vertex o{};
            o.position={center.x+a*cosT,center.y+b*sinT};
            o.color={
                _borderColor.r/255.0f,
                _borderColor.g/255.0f,
                _borderColor.b/255.0f,
                _borderColor.a/255.0f
            };

            SDL_Vertex in{};
            in.position={center.x+innerA*cosT,center.y+innerB*sinT};
            in.color=o.color;

            bVertices.push_back(o);
            bVertices.push_back(in);
        }

        for(int i=0;i<segments;i++){
            int idx=i*2;

            bIndices.push_back(idx);
            bIndices.push_back(idx+1);
            bIndices.push_back(idx+2);

            bIndices.push_back(idx+1);
            bIndices.push_back(idx+3);
            bIndices.push_back(idx+2);
        }

        SDL_RenderGeometry(__renderer,nullptr,bVertices.data(),(int)bVertices.size(),bIndices.data(),(int)bIndices.size());
    }

    SDL_SetRenderDrawBlendMode(__renderer,SDL_BLENDMODE_NONE);
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