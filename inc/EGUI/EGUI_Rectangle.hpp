#pragma once
#include "EGUI_Shape.hpp"
struct SDL_Rect;

namespace egui{
	class Rectangle : public Shape{
	public:
		constexpr Vector2D getSize() const { return _size; }
		inline void setSize(const Vector2D& size) { _size = size; _hitbox.setSize(_size); }

		Rectangle(	const Vector2D& size, 
					const Vector2D& pos, 
					const Color_RGBA& bgColor=egui::colors::Red, 
					const float bdWidth=0, 
					const Color_RGBA& bdColor=egui::colors::Transparent, 
					const float rotRad=0);
		Rectangle();
	private:
		Vector2D _size{0, 0};

		void _draw(SDL_Renderer* __renderer) override;
	};
}