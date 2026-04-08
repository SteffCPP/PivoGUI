#pragma once
#include "EGUI_Shape.hpp"
struct SDL_Rect;

namespace egui{
	class Rectangle : public Shape{
	public:
		Rectangle(	const Vector2D& size, 
					const Vector2D& pos, 
					const Color_RGBA& bgColor=egui::colors::Red, 
					const double bdWidth=0, 
					const Color_RGBA& bdColor=egui::colors::Transparent, 
					const double rotRad=0);
		Rectangle();
	private:
		void _draw(SDL_Renderer* __renderer) override;
	};
}