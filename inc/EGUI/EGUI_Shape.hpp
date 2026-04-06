#pragma once
#include "EGUI_Color.hpp"
#include "EGUI_Vector2D.hpp"
#include "EGUI_Math.hpp"

namespace egui{
	class Shape{
	public:
		constexpr virtual Vector2D& position(){ return _pos; }
		constexpr virtual Color_RGBA& backgroundColor(){ return _backgroundColor; }
		constexpr virtual Color_RGBA& borderColor(){ return _borderColor; }

		constexpr virtual float& rotationDegrees(){ return _rotationDegrees; }
		constexpr virtual float& rotationRadians(){ return _rotationRadians; }

	protected:
		Vector2D _pos{0, 0};

		float _rotationDegrees{0}, _rotationRadians{0};

		float _borderWidth{0};
		Color_RGBA _backgroundColor{0,0,0,0}, _borderColor{0,0,0,0};
	};
}