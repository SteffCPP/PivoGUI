#pragma once
#include "EGUI_Shape.hpp"
#include <vector>

namespace egui{
	class Circle : public Shape{
	public:
		constexpr float getRadius() const { return _radius; }
		void setRadius(float radius){ _radius = radius; }

		Circle(	const float radius, 
				const Vector2D& pos,
				const Color_RGBA& bgColor=colors::Red, 
				const float bdWidth=0, 
				const Color_RGBA& bdColor=colors::Transparent){
			_radius = radius;
			_pos = pos;
			_backgroundColor = bgColor;
			_borderWidth = bdWidth;
			_borderColor = bdColor;
			_type = WidgetType::CIRCLE;
		}
		Circle(){}
	private:
		void _draw(SDL_Renderer* __renderer) override;

		inline void _drawFilledCircle(	SDL_Renderer* __renderer, 
										const float __cx,
										const float __cy,
										const float __radius,
										const Color_RGBA& __color);

		float _radius{0};
	};
}