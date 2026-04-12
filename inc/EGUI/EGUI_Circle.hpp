#pragma once

#include "EGUI_Dep.hpp"
#include "EGUI_Widget.hpp"

#include <vector>

namespace egui{
	class Circle : public Widget{
	public:
		float getRadius() const { return _radius; }
		void setRadius(float radius){ 
			_radius = radius; 
			setSize({radius*2, radius*2});
		}

		virtual bool containsPoint(const Vector2D& point) const override {
			auto c = getPosition();

			float dx = point.x - (c.x + _radius);
			float dy = point.y - (c.y + _radius);

			return dx*dx + dy*dy <= _radius*_radius;
		}


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