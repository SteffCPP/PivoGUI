#include "EGUI_Rectangle.hpp"
#include "SDL.h"

namespace egui{
Rectangle::Rectangle(	const Vector2D& size, 
						const Vector2D& pos, 
						const Color_RGBA& bgColor, 
						const double bdWidth, 
						const Color_RGBA& bdColor, 
						const double rotRad){
			
	_size = size;
	_pos = pos;
	_backgroundColor = bgColor;
	_borderWidth = bdWidth;
	_borderColor = bdColor;
	_rotationRadians = rotRad;
	_rotationDegrees = math::radToDeg(rotRad);

	_hitbox.setPosition(pos);
	_hitbox.setSize(size);
}
Rectangle::Rectangle(){}

void Rectangle::_draw(SDL_Renderer* __renderer) {
	Widget::Hitbox::FRect hitboxFRect = _hitbox.getRect();
	SDL_FRect drawRect{hitboxFRect.x, hitboxFRect.y, hitboxFRect.w, hitboxFRect.h};
	SDL_SetRenderDrawColor(__renderer, _borderColor.R(), _borderColor.G(), _borderColor.B(), _borderColor.A());
	SDL_RenderFillRect(__renderer, &drawRect);

	drawRect.x+=_borderWidth;
	drawRect.y+=_borderWidth;
	drawRect.w-=_borderWidth*2;
	drawRect.h-=_borderWidth*2;
	SDL_SetRenderDrawColor(__renderer, _backgroundColor.R(), _backgroundColor.G(), _backgroundColor.B(), _backgroundColor.A());
	SDL_RenderFillRect(__renderer, &drawRect);
}
}
