#pragma once 

namespace egui{
	class Vector2D{
	public:
		constexpr double X() const { return _x; };
		constexpr double Y() const { return _y; };

		void setX(double X){ _x = X; };
		void setY(double Y){ _y = Y; };

		Vector2D(const double X, const double Y) : _x(X), _y(Y) {};
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
        constexpr Vector2D operator*(double s) const {
            return { _x * s, _y * s };
        }
        constexpr Vector2D operator/(const Vector2D& v) const {
            return { _x / v._x, _y / v._y };
        }
        constexpr Vector2D operator/(double s) const {
            return { _x / s, _y / s };
        }
	private:
		double _x{0}, _y{0};
	};
} 
