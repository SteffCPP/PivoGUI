#pragma once
#include "EGUI_Shape.hpp"

namespace egui{
	class Rectangle : public Shape{
	public:
		constexpr Vector2D getSize(){ return _size; }

		Rectangle(const Vector2D size, const Vector2D pos, const Color_RGBA bgColor=egui::colors::Red, const double bordWidth=0, const Color_RGBA bdColor=egui::colors::Transparent, const double rotRad=0){
			_size = size;
			_pos = pos;
			_backgroundColor = bgColor;
			_borderWidth = bordWidth;
			_borderColor = bdColor;
			_rotationRadians = rotRad;
			_rotationDegrees = egui::math::radToDeg(rotRad);
		}
	private:
		void _draw(SDL_Renderer* __renderer) override {
			SDL_FRect drawRect;
			drawRect.x = _pos.X();
			drawRect.y = _pos.Y();
			drawRect.w = _size.X();
			drawRect.h = _size.Y();
			SDL_SetRenderDrawColor(__renderer, _borderColor.R(), _borderColor.G(), _borderColor.B(), _borderColor.A());
			SDL_RenderFillRect(__renderer, &drawRect);

			drawRect.x+=_borderWidth;
			drawRect.y+=_borderWidth;
			drawRect.w-=_borderWidth*2;
			drawRect.h-=_borderWidth*2;
			SDL_SetRenderDrawColor(__renderer, _backgroundColor.R(), _backgroundColor.G(), _backgroundColor.B(), _backgroundColor.A());
			SDL_RenderFillRect(__renderer, &drawRect);
		}

		Vector2D _size{0, 0};
	};
}