#pragma once
#include "EGUI_Shape.hpp"
#include "EGUI_Color.hpp"
#include "EGUI_Vector2D.hpp"
#include "EGUI_Math.hpp"

namespace egui{
	class Rectangle : public Shape{
	public:
		constexpr Vector2D& size(){ return _size; }

		Rectangle() = default;
		~Rectangle() = default;
	private:
		Vector2D _size{0, 0};
	};
}