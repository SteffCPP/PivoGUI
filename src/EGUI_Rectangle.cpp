#include "EGUI_Rectangle.hpp"
#include "EGUI_SDL.cpp"

namespace egui{
Rectangle::Rectangle(	const Vector2D& size, 
						const Vector2D& pos, 
						const Color_RGBA& bgColor, 
						const float bdWidth, 
						const Color_RGBA& bdColor, 
						const float rotRad){
			
	_size = size;
	_pos = pos;
	_backgroundColor = bgColor;
	_borderWidth = bdWidth;
	_borderColor = bdColor;
	_rotationRadians = rotRad;
	_rotationDegrees = math::radToDeg(rotRad);
	_type = WidgetType::RECTANGLE;

	_hitbox.setPosition(pos);
	_hitbox.setSize(size);
}
Rectangle::Rectangle(){}

void Rectangle::_draw(SDL_Renderer* __renderer) {
	SDL_FRect drawRect{_hitbox.getPosition().X(), _hitbox.getPosition().Y(), _hitbox.getSize().X(), _hitbox.getSize().Y()};
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
