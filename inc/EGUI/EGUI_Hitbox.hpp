#pragma once

#include "EGUI_Vector.hpp"
#include "EGUI_Dep.hpp"

#include <functional>

namespace egui{
	class Hitbox{
	public:
		Vector2D getPosition() const { return {_x, _y}; }
		Vector2D getSize() const { return {_w, _h}; }
		
		inline void setPosition(const Vector2D& pos){ _x = pos.X(); _y = pos.Y(); }
		inline void setSize(const Vector2D& size) { _w = size.X(); _h = size.Y(); }
				
		Hitbox(const Vector2D& size, const Vector2D& pos){
			_x = pos.X();
			_y = pos.Y();
			_w = size.X();
			_h = size.Y();
		}
		Hitbox(const float x, const float y, const float w, const float h){
			_x = x;
			_y = y;
			_w = w;
			_h = h;
		}
	private:
		float _x{0}, _y{0}, _w{0}, _h{0};
	};
}