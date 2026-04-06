#pragma once
#include "EGUI_Shape.hpp"

namespace egui{
	class Circle : public Shape{
	public:
		constexpr double& radius(){ return _radius; }
	private:
		void _draw(SDL_Renderer* __renderer) override {

		}

		double _radius{0};
	};
}