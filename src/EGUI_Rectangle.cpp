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

#include "EGUI_Rectangle.hpp"
#include "EGUI_SDL.cpp"
#include <iostream>

namespace egui{
bool Rectangle::containsPoint(const Vector2D& point) const {
	return point.x >= _pos.x &&
		point.x <= _pos.x + _size.x &&
		point.y >= _pos.y &&
		point.y <= _pos.y + _size.y;
}

Rectangle::Rectangle(	const Vector2D& size, 
						const Vector2D& pos, 
						const Color_RGBA& bgColor, 
						const float bdWidth, 
						const Color_RGBA& bdColor, 
						const float rotDeg){
			
	_size = size;
	_pos = pos;
	_backgroundColor = bgColor;
	_borderWidth = bdWidth;
	_borderColor = bdColor;
	_rotation = rotDeg;
	_type = WidgetType::RECTANGLE;
}
Rectangle::Rectangle(){}

void Rectangle::_draw(SDL_Renderer* __renderer) {
	if(_hide) return;
	SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

	Vector2D offset = _computePivotOffset();
	Vector2D finalPos = _pos - offset;

	SDL_FRect drawRect{finalPos.x, finalPos.y, _size.x, _size.y};

	SDL_SetRenderDrawColor(
		__renderer,
		_borderColor.r,
		_borderColor.g,
		_borderColor.b,
		_borderColor.a
	);

	float x = std::round(drawRect.x);
	float y = std::round(drawRect.y);
	float w = std::round(drawRect.w);
	float h = std::round(drawRect.h);
	float b = _borderWidth;

	for (int i = 0; i < _borderWidth; i++) {
		SDL_FRect borderRect{
			x + i,
			y + i,
			w - 2.0f * i,
			h - 2.0f * i
		};

		SDL_RenderRect(__renderer, &borderRect);
	}

	SDL_FRect innerRect{
		finalPos.x + _borderWidth,
		finalPos.y + _borderWidth,
		_size.x - _borderWidth * 2,
		_size.y - _borderWidth * 2
	};

	SDL_SetRenderDrawColor(
		__renderer,
		_backgroundColor.r,
		_backgroundColor.g,
		_backgroundColor.b,
		_backgroundColor.a
	);
	SDL_RenderFillRect(__renderer, &innerRect);

	if (_hasImage) {
		SDL_Surface* image = IMG_Load(_img.getPath().c_str());
		if (!image) {
			std::cerr << "IMG_Load() error (error rendering image): "
					  << SDL_GetError() << "\n";
			return;
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(__renderer, image);

		SDL_RenderTexture(__renderer, tex, NULL, &innerRect);

		SDL_DestroyTexture(tex);
		SDL_DestroySurface(image);
	}

	SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
}
}
