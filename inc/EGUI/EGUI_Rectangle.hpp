#pragma once

#include "EGUI_Widget.hpp"

struct SDL_Rect;

namespace egui{
	class Rectangle : public Widget{
	public:
		virtual bool containsPoint(const Vector2D& point) const override {
			auto pos = getPosition();
			auto size = getSize();

			return point.x >= pos.x &&
				point.x <= pos.x + size.x &&
				point.y >= pos.y &&
				point.y <= pos.y + size.y;
		}

		Rectangle(	const Vector2D& size, 
					const Vector2D& pos, 
					const Color_RGBA& bgColor=egui::colors::Red, 
					const float bdWidth=0, 
					const Color_RGBA& bdColor=egui::colors::Transparent, 
					const float rotRad=0);
		Rectangle();
	private:
		void _draw(SDL_Renderer* __renderer) override;
	};
}