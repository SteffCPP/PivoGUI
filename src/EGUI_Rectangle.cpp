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
}
Rectangle::Rectangle(){}

void Rectangle::_draw(SDL_Renderer* __renderer) {
	Vector2D offset = _computePivotOffset();
	Vector2D finalPos = _pos - offset;

	SDL_FRect drawRect{finalPos.x, finalPos.y, _size.x, _size.y};
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
