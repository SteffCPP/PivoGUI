#pragma once
#include "EGUI_Shape.hpp"
#include "EGUI_Color.hpp"
#include "EGUI_Vector2D.hpp"
#include "EGUI_Math.hpp"

namespace egui{
	class Rectangle : public Shape{
	public:
		constexpr Vector2D& size(){ return _size; }
	private:
		void _draw(SDL_Renderer* __renderer) override {
			SDL_FRect drawRect;
			drawRect.x = _pos.X();
			drawRect.y = _pos.Y();
			drawRect.w = _size.X();
			drawRect.h = _size.Y();
			SDL_SetRenderDrawColor(__renderer, _borderColor.R(), _borderColor.G(), _borderColor.B(), _borderColor.A());
			SDL_RenderRect(__renderer, &drawRect);

			SDL_SetRenderDrawColor(__renderer, _backgroundColor.R(), _backgroundColor.G(), _backgroundColor.B(), _backgroundColor.A());
			SDL_RenderFillRect(__renderer, &drawRect);
		}

		Vector2D _size{0, 0};
	};
}