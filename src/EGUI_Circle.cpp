/*
EGUI - Embedded Graphics Utility Interface
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

#include "EGUI_Circle.hpp"
#include "EGUI_SDL.cpp"
#include <iostream>

namespace egui{
float Circle::getRadius() const { return _radius; }
void Circle::setRadius(float radius){ 
	_radius = radius;
	setSize({radius*2, radius*2});
}
bool Circle::containsPoint(const Vector2D& point) const {
	auto c = getPosition();

	float dx = point.x - (c.x + _radius);
	float dy = point.y - (c.y + _radius);

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
	_type = WidgetType::CIRCLE;
}
Circle::Circle(){}


void Circle::_draw(SDL_Renderer* __renderer) {
	if(_hide) return;
	SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

	Vector2D pivotOffset = _computePivotOffset();
	Vector2D centerOffset = pivotOffset - Vector2D{_radius, _radius};
	Vector2D finalCenter = _pos - centerOffset;

	float cx = std::round(finalCenter.x);
	float cy = std::round(finalCenter.y);

	float rOuter = std::round(_radius);
	float rInner = std::round(_radius - _borderWidth);

	// Background 
	SDL_SetRenderDrawColor(
		__renderer,
		_backgroundColor.r,
		_backgroundColor.g,
		_backgroundColor.b,
		_backgroundColor.a
	);
	_drawFilledCircle(__renderer, cx, cy, rInner, _backgroundColor);

	// Image
	if (_hasImage) {
		SDL_Surface* image = IMG_Load(_img.getPath().c_str());
		if (!image) {
			std::cerr << "IMG_Load error: " << SDL_GetError() << "\n";
			return;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(__renderer, image);
		SDL_DestroySurface(image);

		float innerRadius = _radius - _borderWidth;
		if (innerRadius < 0) innerRadius = 0;

		int size = (int)(innerRadius * 2.0f);

		SDL_FRect dst{
			cx - innerRadius,
			cy - innerRadius,
			(float)size,
			(float)size
		};

		SDL_RenderTexture(__renderer, tex, nullptr, &dst);

		SDL_DestroyTexture(tex);
	}
	
	SDL_SetRenderDrawColor(
		__renderer,
		_borderColor.r,
		_borderColor.g,
		_borderColor.b,
		_borderColor.a
	);

	// Border
	for (int y = -rOuter; y <= rOuter; y++) {
		int xOuter = (int)std::floor(std::sqrt(rOuter * rOuter - y * y));
		int xInner = (rInner > 0 && abs(y) <= rInner)
			? (int)std::floor(std::sqrt(rInner * rInner - y * y))
			: 0;

		int yPos = cy + y;

		// Left side
		SDL_RenderLine(__renderer,
			cx - xOuter, yPos,
			cx - xInner, yPos
		);

		// Right side
		SDL_RenderLine(__renderer,
			cx + xInner, yPos,
			cx + xOuter, yPos
		);
	}
}

inline void Circle::_drawFilledCircle(
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

	int cx = (int)std::round(__cx);
	int cy = (int)std::round(__cy);
	int r  = (int)std::round(__radius);

	for (int y = -r; y <= r; y++) {
		int xSpan = (int)std::floor(std::sqrt(r * r - y * y));

		int x1 = cx - xSpan;
		int x2 = cx + xSpan;
		int yy = cy + y;

		SDL_RenderLine(__renderer, x1, yy, x2, yy);
	}
}
}
