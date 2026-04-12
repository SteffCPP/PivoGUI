#pragma once 

namespace egui{
	struct Vector2D{
        float x{0}, y{0};

		constexpr Vector2D operator+(const Vector2D& v) const {
            return { x + v.x, y + v.y };
        }
        constexpr Vector2D operator-(const Vector2D& v) const {
            return { x - v.x, y - v.y };
        }
        constexpr Vector2D operator*(const Vector2D& v) const {
            return { x * v.x, y * v.y };
        }
        constexpr Vector2D operator*(float s) const {
            return { x * s, y * s };
        }
        constexpr Vector2D operator/(const Vector2D& v) const {
            return { x / v.x, y / v.y };
        }
        constexpr Vector2D operator/(float s) const {
            return { x / s, y / s };
        }
	};
} 
