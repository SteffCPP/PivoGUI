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

#include "PIVO_Circle.hpp"
#include "PIVO_SDL.cpp"
#include "PIVO_TextureManager.hpp"

#include <iostream>

namespace pivo{
float Circle::getRadius() const { return _radius; }
void Circle::setRadius(float radius){ 
	_radius = radius;
	_size = {radius*2, radius*2};
}
void Circle::setSize(const Vector2D& size){
	std::cerr << "Cannot set size to Circle. Use setRadius() instead.\n"; 
	return;
}
Vector2D Circle::getSize() const{
	std::cerr << "Cannot get size of Circle. Use getRadius() instead.\n"; 
	return {0,0};
}

bool Circle::containsPoint(const Vector2D& point) const {
	float dx = point.x - (_pos.x + _radius);
	float dy = point.y - (_pos.y + _radius);

	return dx*dx + dy*dy <= _radius*_radius;
}
Circle::Circle(	const float radius, 
				const Vector2D& pos,
				const Color_RGBA& bgColor, 
				const float bdWidth, 
				const Color_RGBA& bdColor){
	_radius = radius;
	_pos = pos;
	_backgroundColor = bgColor;
	_borderWidth = bdWidth;
	_borderColor = bdColor;
	_size = {_radius*2, _radius*2};
}
Circle::Circle(){}


void Circle::_draw(SDL_Renderer* __renderer) {
	if (_hide) return;
	SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

	Vector2D topLeft = _pos + _computePivotOffset();

	float cx = topLeft.x + _radius;
	float cy = topLeft.y + _radius;

	float rOuter = _radius;
	float rInner = _radius - _borderWidth;
	if (rInner < 0) rInner = 0;

	SDL_SetRenderDrawColor(
		__renderer,
		_backgroundColor.r,
		_backgroundColor.g,
		_backgroundColor.b,
		_backgroundColor.a
	);

	_drawFilledCircle(__renderer, cx, cy, rInner, _backgroundColor);

	if (_hasImage) {
		SDL_Texture* tex = Texture_Manager::load(_img.getPath());

		float innerRadius = _radius - _borderWidth;
		if (innerRadius < 0) innerRadius = 0;

		SDL_FRect dst{
			cx - innerRadius,
			cy - innerRadius,
			innerRadius * 2.0f,
			innerRadius * 2.0f
		};

		SDL_FPoint center{
			dst.w / 2.0f,
			dst.h / 2.0f
		};

		SDL_RenderTextureRotated(
			__renderer,
			tex,
			nullptr,
			&dst,
			_rotation,
			&center,
			SDL_FLIP_NONE
		);

		SDL_DestroyTexture(tex);
	}

	SDL_SetRenderDrawColor(
		__renderer,
		_borderColor.r,
		_borderColor.g,
		_borderColor.b,
		_borderColor.a
	);

	for (int y = -rOuter; y <= rOuter; y++) {
		int xOuter = (int)std::floor(std::sqrt(rOuter * rOuter - y * y));
		int xInner = (rInner > 0 && std::abs(y) <= rInner)
			? (int)std::floor(std::sqrt(rInner * rInner - y * y))
			: 0;

		int yPos = cy + y;

		SDL_RenderLine(__renderer,
			cx - xOuter, yPos,
			cx - xInner, yPos
		);

		SDL_RenderLine(__renderer,
			cx + xInner, yPos,
			cx + xOuter, yPos
		);
	}
}

void Circle::_drawFilledCircle(
	SDL_Renderer* __renderer,
	const float __cx,
	const float __cy,
	const float __radius,
	const Color_RGBA& __color
) {
	if (__radius <= 0) return;

	SDL_SetRenderDrawColor(
		__renderer,
		__color.r,
		__color.g,
		__color.b,
		__color.a
	);

	for (int y=-__radius; y<=__radius; y++) {
		int xSpan = (int)std::floor(std::sqrt(__radius*__radius-y*y));

		int x1 = __cx - xSpan;
		int x2 = __cx + xSpan;
		int yy = __cy + y;

		SDL_RenderLine(__renderer, x1, yy, x2, yy);
	}
}
}
