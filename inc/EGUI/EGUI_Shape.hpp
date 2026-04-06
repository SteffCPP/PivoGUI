#pragma once
#include "EGUI_Color.hpp"
#include "EGUI_Vector2D.hpp"
#include "EGUI_Math.hpp"
#include "EGUI_Widget.hpp"

namespace egui{
	class Shape : public Widget{
	public:
		constexpr virtual Vector2D& position(){ return _pos; }
		constexpr virtual Color_RGBA& backgroundColor(){ return _backgroundColor; }
		constexpr virtual Color_RGBA& borderColor(){ return _borderColor; }

		constexpr virtual double& rotationDegrees(){ return _rotationDegrees; }
		constexpr virtual double& rotationRadians(){ return _rotationRadians; }
		
		virtual ~Shape() = default;
	protected:
		Vector2D _pos{0, 0};

		double _rotationDegrees{0}, _rotationRadians{0};

		double _borderWidth{0};
		Color_RGBA _backgroundColor{egui::colors::Black}, _borderColor{egui::colors::Transparent};
	};
}