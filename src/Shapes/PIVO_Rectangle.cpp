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

#include "PIVO/Shapes/PIVO_Rectangle.hpp"
#include "PIVO/Systems/PIVO_TextureSys.hpp"
#include "../PIVO_SDL.cpp"

#include <iostream>

namespace pivo{
bool Rectangle::containsPoint(const Vector2D& point) const {
	return point.x >= _pos.x &&
		point.x <= _pos.x + _size.x &&
		point.y >= _pos.y &&
		point.y <= _pos.y + _size.y;
}

Rectangle::Rectangle(	const Vector2D& size, 
						const Vector2D& pos, 
						const Color_RGBA& color,
						const float bdWidth, 
						const Color_RGBA& bdColor, 
						const float rotDeg){
			
	_size = size;
	_pos = pos;
	_color = color;
	_borderWidth = bdWidth;
	_borderColor = bdColor;
	_rotation = rotDeg;
}
Rectangle::Rectangle(){}

Vector2D Rectangle::_computePivotOffset() const {
    switch(_pivot){
		case Pivot::TOP_LEFT:     return {0, 0};
		case Pivot::TOP:          return {-_size.x / 2, 0};
		case Pivot::TOP_RIGHT:    return {-_size.x, 0};

		case Pivot::LEFT:         return {0, -_size.y / 2};
		case Pivot::CENTER:       return {-_size.x / 2, -_size.y / 2};
		case Pivot::RIGHT:        return {-_size.x, -_size.y / 2};

		case Pivot::BOTTOM_LEFT:  return {0, -_size.y};
		case Pivot::BOTTOM:       return {-_size.x / 2, -_size.y};
		case Pivot::BOTTOM_RIGHT: return {-_size.x, -_size.y};
	}
	return {0, 0};
}

void Rectangle::_draw(SDL_Renderer* __renderer) {
	if(_hide) return;
	SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

	Vector2D finalPos = _pos + _computePivotOffset();

	// Faster rendering without rotation
	if(!_hasRotation()){
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
			_color.r,
			_color.g,
			_color.b,
			_color.a
		);
		SDL_RenderFillRect(__renderer, &innerRect);

		if (_hasTexture) {
			Texture_Manager::load(_texture);
			SDL_RenderTexture(__renderer, Texture_Manager::getSDLTexture(_texture), NULL, &innerRect);
		}

		SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
		return;
	}
	
	SDL_Texture* target = SDL_CreateTexture(
        __renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        (int)_size.x,
        (int)_size.y
    );

    SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(__renderer, target);

    SDL_SetRenderDrawColor(__renderer, 0, 0, 0, 0);
    SDL_RenderClear(__renderer);

    SDL_FRect localRect{0, 0, _size.x, _size.y};

    SDL_SetRenderDrawColor(
        __renderer,
        _borderColor.r,
        _borderColor.g,
        _borderColor.b,
        _borderColor.a
    );

    for (int i = 0; i < _borderWidth; i++) {
        SDL_FRect borderRect{
            (float)i,
            (float)i,
            _size.x - 2.0f * i,
            _size.y - 2.0f * i
        };
        SDL_RenderRect(__renderer, &borderRect);
    }

    SDL_FRect innerRect{
        (float)_borderWidth,
        (float)_borderWidth,
        _size.x - _borderWidth * 2,
        _size.y - _borderWidth * 2
    };

    SDL_SetRenderDrawColor(
        __renderer,
        _color.r,
        _color.g,
        _color.b,
        _color.a
    );
    SDL_RenderFillRect(__renderer, &innerRect);

    if (_hasTexture)
        SDL_RenderTexture(__renderer, Texture_Manager::getSDLTexture(_texture), NULL, &innerRect);
    

    SDL_SetRenderTarget(__renderer, NULL);

    SDL_FRect dst{finalPos.x, finalPos.y, _size.x, _size.y};
    SDL_FPoint center{
        _size.x / 2.0f,
        _size.y / 2.0f
    };

    SDL_RenderTextureRotated(
        __renderer,
        target,
        NULL,
        &dst,
        _rotation,
        &center,
        SDL_FLIP_NONE
    );

    SDL_DestroyTexture(target);
    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
}
}
