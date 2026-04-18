/*
EGUI - Embedded Graphics Utility Interface
Copyright (c) 2026 Stefano Rando (randostefano39@proton.me)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required. 
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#pragma once

#include "EGUI_Dep.hpp"
#include "EGUI_Widget.hpp"

#include <vector>

namespace egui{
	class Circle : public Widget, public texturable{
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