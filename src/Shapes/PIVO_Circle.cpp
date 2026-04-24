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

#include "PIVO/Shapes/PIVO_Circle.hpp"
#include "PIVO/Systems/PIVO_TextureSys.hpp"
#include "../PIVO_SDL.cpp"


#include <iostream>

namespace pivo{
float Circle::getRadius() const { return _radius; }
void Circle::setRadius(float radius){ _radius = radius; }

bool Circle::containsPoint(const Vector2D& point) const {
	float dx = point.x - (_pos.x + _radius);
	float dy = point.y - (_pos.y + _radius);

	return dx*dx + dy*dy <= _radius*_radius;
}
Circle::Circle(	const float radius, 
				const Vector2D& pos,
				const Color_RGBA& color, 
				const float bdWidth, 
				const Color_RGBA& bdColor){
	_radius = radius;
	_pos = pos;
	_color = color;
	_borderWidth = bdWidth;
	_borderColor = bdColor;
}
Circle::Circle(){}

Vector2D Circle::_computePivotOffset() const {
	switch(_pivot){
		case Pivot::TOP_LEFT:     return {0, 0};
		case Pivot::TOP:          return {-_radius*2 / 2, 0};
		case Pivot::TOP_RIGHT:    return {-_radius*2, 0};

		case Pivot::LEFT:         return {0, -_radius*2 / 2};
		case Pivot::CENTER:       return {-_radius*2 / 2, -_radius*2 / 2};
		case Pivot::RIGHT:        return {-_radius*2, -_radius*2 / 2};

		case Pivot::BOTTOM_LEFT:  return {0, -_radius*2};
		case Pivot::BOTTOM:       return {-_radius*2 / 2, -_radius*2};
		case Pivot::BOTTOM_RIGHT: return {-_radius*2, -_radius*2};
	}
	return {0, 0};
}

void Circle::_draw(SDL_Renderer* __renderer){
    if(!__renderer||_hide)return;

    Vector2D pos=getPosition();
    Vector2D pivotOffset=_computePivotOffset();

    float cx=pos.x+_radius-pivotOffset.x;
    float cy=pos.y+_radius-pivotOffset.y;

    SDL_Texture* tex=nullptr;

    if(_hasAnim&&_currAnim){
        Texture t=_currAnim->getCurrentFrame();
        tex=Texture_Manager::getSDLTexture(t);
    }else if(_hasTexture){
        tex=Texture_Manager::getSDLTexture(_texture);
    }

    const int segments=40;

    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    SDL_Vertex center{};
    center.position={cx,cy};
    center.color={1.0f,1.0f,1.0f,1.0f};
    center.tex_coord={0.5f,0.5f};

    if(!tex){
        center.color={
            _color.r/255.0f,
            _color.g/255.0f,
            _color.b/255.0f,
            _color.a/255.0f
        };
        center.tex_coord={0,0};
    }

    vertices.push_back(center);

    for(int i=0;i<=segments;i++){
        float a=(float)i/segments*2.0f*M_PI;

        float x=cx+cos(a)*_radius;
        float y=cy+sin(a)*_radius;

        float u=cos(a)*0.5f+0.5f;
        float v=sin(a)*0.5f+0.5f;

        SDL_Vertex vtx{};
        vtx.position={x,y};

        if(tex){
            vtx.color={1.0f,1.0f,1.0f,1.0f};
            vtx.tex_coord={u,v};
        }else{
            vtx.color={
                _color.r/255.0f,
                _color.g/255.0f,
                _color.b/255.0f,
                _color.a/255.0f
            };
            vtx.tex_coord={0,0};
        }

        vertices.push_back(vtx);
    }

    for(int i=1;i<=segments;i++){
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i+1);
    }

    SDL_RenderGeometry(__renderer,tex,vertices.data(),(int)vertices.size(),indices.data(),(int)indices.size());

    if(_borderWidth>0){
        float innerR=_radius-_borderWidth;
        if(innerR<0)innerR=0;

        std::vector<SDL_Vertex> bVertices;
        std::vector<int> bIndices;

        for(int i=0;i<=segments;i++){
            float a=(float)i/segments*2.0f*M_PI;

            float cosA=cos(a);
            float sinA=sin(a);

            SDL_Vertex o{};
            o.position={cx+cosA*_radius,cy+sinA*_radius};
            o.color={
                _borderColor.r/255.0f,
                _borderColor.g/255.0f,
                _borderColor.b/255.0f,
                _borderColor.a/255.0f
            };

            SDL_Vertex in{};
            in.position={cx+cosA*innerR,cy+sinA*innerR};
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
}

void Circle::_drawFilledCircle(
    SDL_Renderer* __renderer,
    const float __cx,
    const float __cy,
    const float __radius,
    const Color_RGBA& __color
){
    if(__radius <= 0) return;

    const int segments = 40;

    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    SDL_Vertex center{};
    center.position = {__cx, __cy};
    center.color = {(float)__color.r, (float)__color.g, (float)__color.b, (float)__color.a};
    center.tex_coord = {0,0}; // non usata

    vertices.push_back(center);

    for(int i=0; i<=segments; ++i){
        float angle = (float)i / segments * 2.0f * math::PI;

        float x = __cx+cos(angle) * __radius;
        float y = __cy+sin(angle) * __radius;

        SDL_Vertex v{};
        v.position = {x, y};
        v.color = {(float)__color.r, (float)__color.g, (float)__color.b, (float)__color.a};
        v.tex_coord = {0,0};

        vertices.push_back(v);
    }

    for(int i=1; i<=segments; ++i){
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i+1);
    }

    SDL_RenderGeometry(
        __renderer,
        nullptr,
        vertices.data(),
        vertices.size(),
        indices.data(),
        indices.size()
    );
}
void Circle::_drawCircleBorder(
    SDL_Renderer* __renderer,
    const float __cx, float __cy,
    const float __radius,
    const float __borderWidth,
    const Color_RGBA& __color
){
    if(__borderWidth <= 0) return;

    const int segments = 40;

    float innerR = __radius-__borderWidth;
    if(innerR < 0) innerR = 0;

    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

    for(int i=0; i<=segments; ++i){
        float angle = (float)i / segments * 2.0f * math::PI;

        float cosA = cos(angle);
        float sinA = sin(angle);

        SDL_Vertex vOuter{};
        vOuter.position = {__cx+cosA * __radius, __cy+sinA * __radius};
        vOuter.color = {(float)__color.r, (float)__color.g, (float)__color.b, (float)__color.a};

        SDL_Vertex vInner{};
        vInner.position = {__cx+cosA * innerR, __cy+sinA * innerR};
        vInner.color = {(float)__color.r, (float)__color.g, (float)__color.b, (float)__color.a};

        vertices.push_back(vOuter);
        vertices.push_back(vInner);
    }

    for(int i = 0; i <= segments; ++i){
        int idx = i * 2;

        indices.push_back(idx);
        indices.push_back(idx+1);
        indices.push_back(idx+2);

        indices.push_back(idx+1);
        indices.push_back(idx+3);
        indices.push_back(idx+2);
    }

    SDL_RenderGeometry(
        __renderer,
        nullptr,
        vertices.data(),
        vertices.size(),
        indices.data(),
        indices.size()
    );
}
}
