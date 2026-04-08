#pragma once
#include "EGUI_Color.hpp"
#include "EGUI_Vector2D.hpp"
#include "EGUI_Math.hpp"
#include "EGUI_Widget.hpp"

namespace egui{
	class Shape : public Widget{
	public:
		constexpr Vector2D getPosition() const { return _pos; }
		constexpr Color_RGBA getBackgroundColor() const { return _backgroundColor; }
		constexpr Color_RGBA getBorderColor() const { return _borderColor; }
		constexpr double getBorderWidth() const { return _borderWidth; }
		constexpr double getRotationDegrees() const { return _rotationDegrees; }
		constexpr double getRotationRadians() const { return _rotationRadians; }

		inline void setPosition(const Vector2D& pos){ _pos = pos; }
		inline void move(const Vector2D& delta){ _pos = _pos + delta; }
		inline void setBackgroundColor(const Color_RGBA& color){ _backgroundColor = color; }
		inline void setBorderColor(const Color_RGBA& color){ _borderColor = color; }
		inline void setBorderWidth(const double width){ _borderWidth = width; }
		inline void setRotationDegrees(double deg){ 
			_rotationDegrees = deg; 
			_rotationRadians = egui::math::degToRad(deg);
		}
		inline void setRotationRadians(double rad){ 
			_rotationRadians = rad;
			_rotationDegrees = egui::math::radToDeg(rad);
		}
		
		virtual ~Shape() = default;
	protected:
		Vector2D _pos{0, 0};

		double _rotationDegrees{0}, _rotationRadians{0};

		double _borderWidth{0};
		Color_RGBA _backgroundColor{egui::colors::Black}, _borderColor{egui::colors::Transparent};
	};
}