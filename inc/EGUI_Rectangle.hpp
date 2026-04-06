#pragma once
#include "EGUI_Shape.hpp"
#include "EGUI_Color.hpp"
#include "EGUI_Vector2D.hpp"
#include "EGUI_Math.hpp"

namespace egui{
	class Rectangle : public Shape{
	public:
		inline void setSize(Vector2D size){ _width = size.getX(); _height = size.getY(); }
		inline void setPosition(Vector2D position){ _x = position.getX(); _y = position.getY(); }
		inline void setBackgroundColor(const Color_RGBA color){ _backgroundColor = color; }
		inline void setBorderColor(const Color_RGBA color){ _borderColor = color; }
		inline void setRotationDegrees(const float deg){
			_rotationDegrees = deg;
			_rotationRadians = egui::math::degToRad(deg);
		}
		inline void setRotationRadiants(const float rad){
			_rotationRadians = rad;
			_rotationDegrees = egui::math::radToDeg(rad);
		}

		inline Vector2D getSize(){ return {_width, _height}; }
		inline Vector2D getPosition(){ return {_x, _y}; }
		inline Color_RGBA getBackgroundColor(){ return _backgroundColor; }
		inline Color_RGBA getBorderColor(){ return _borderColor; }
		constexpr float getRotationDegrees(){ return _rotationDegrees; }
		constexpr float getRotationRadians(){ return _rotationRadians; }


		Rectangle() = default;
		~Rectangle() = default;
	private:
		float _width{0}, _height{0};
	};
}