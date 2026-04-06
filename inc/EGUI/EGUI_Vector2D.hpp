#pragma once 

namespace egui{
	class Vector2D{
	public:
		constexpr inline double& X(){ return _x; }
		constexpr inline double& Y(){ return _y; }

		Vector2D operator+(const Vector2D& __vec) const {
			return {__vec._x + _x, __vec._y+_y};
		}
		Vector2D operator-(const Vector2D& __vec) const {
			return {__vec._x-_x, __vec._y-_y};
		}
		Vector2D operator*(const Vector2D& __vec) const {
			return {__vec._x*_x, __vec._y*_y};
		}
		Vector2D operator*(const double __x) const {
			return {_x*__x, _y*__x};
		}
		Vector2D operator/(const Vector2D& __vec) const {
			return {__vec._x/_x, __vec._y/_y};
		}
		Vector2D operator/(const double __x) const {
			return {_x/__x, _y/__x};
		}

		Vector2D(){}
		Vector2D(const double X, const double Y) : _x(X), _y(Y) {}
		~Vector2D(){}
	private:
		double _x{0}, _y{0};
	};
} 
