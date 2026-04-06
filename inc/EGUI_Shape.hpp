#pragma once
#include "EGUI_Color.hpp"
#include "EGUI_Vector2D.hpp"
#include "EGUI_Math.hpp"

namespace egui{
	class Shape{
	public:
		virtual void setPosition(Vector2D position) = 0;
		virtual void setBackgroundColor(const Color_RGBA color) = 0;
		virtual void setBorderColor(const Color_RGBA color) = 0;
		virtual void setRotationDegrees(const float deg) = 0;
		virtual void setRotationRadiants(const float rad) = 0;

		virtual Vector2D getPosition() = 0;
		virtual Color_RGBA getBackgroundColor() = 0;
		virtual Color_RGBA getBorderColor() = 0;
		constexpr virtual float getRotationDegrees() = 0;
		constexpr virtual float getRotationRadians() = 0;

	protected:
		float _x{0}, _y{0};

		float _rotationDegrees{0}, _rotationRadians{0};

		float _borderWidth{0};
		Color_RGBA _backgroundColor{0,0,0,0}, _borderColor{0,0,0,0};
	};
}