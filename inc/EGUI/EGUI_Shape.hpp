#pragma once
#include "EGUI_Color.hpp"
#include "EGUI_Vector.hpp"
#include "EGUI_Math.hpp"
#include "EGUI_Widget.hpp"

namespace egui{
	class Shape : public Widget{
	public:
		constexpr Color_RGBA getBackgroundColor() const { return _backgroundColor; }
		constexpr Color_RGBA getBorderColor() const { return _borderColor; }
		constexpr double getBorderWidth() const { return _borderWidth; }

		inline void move(const Vector2D& delta) { _pos = _pos + delta; }
		inline void setBackgroundColor(const Color_RGBA& color) { _backgroundColor = color; }
		inline void setBorderColor(const Color_RGBA& color) { _borderColor = color; }
		inline void setBorderWidth(const double width) { _borderWidth = width; }
		
		Shape(){ _type = WidgetType::SHAPE; }
		virtual ~Shape() = default;
	protected:
		double _borderWidth{0};
		Color_RGBA _backgroundColor{egui::colors::Black}, _borderColor{egui::colors::Transparent};
	};
}