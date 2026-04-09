#pragma once 

namespace egui{
	class Vector2D{
	public:
		constexpr float X() const { return _x; };
		constexpr float Y() const { return _y; };

		void setX(float X){ _x = X; };
		void setY(float Y){ _y = Y; };

		Vector2D(const float X, const float Y) : _x(X), _y(Y) {};
		~Vector2D(){};

		constexpr Vector2D operator+(const Vector2D& v) const {
            return { _x + v._x, _y + v._y };
        }
        constexpr Vector2D operator-(const Vector2D& v) const {
            return { _x - v._x, _y - v._y };
        }
        constexpr Vector2D operator*(const Vector2D& v) const {
            return { _x * v._x, _y * v._y };
        }
        constexpr Vector2D operator*(float s) const {
            return { _x * s, _y * s };
        }
        constexpr Vector2D operator/(const Vector2D& v) const {
            return { _x / v._x, _y / v._y };
        }
        constexpr Vector2D operator/(float s) const {
            return { _x / s, _y / s };
        }
	private:
		float _x{0}, _y{0};
	};
} 
