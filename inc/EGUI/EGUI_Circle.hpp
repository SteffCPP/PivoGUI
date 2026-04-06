#pragma once
#include "EGUI_Shape.hpp"

namespace egui{
	class Circle : public Shape{
	public:
		constexpr double getRadius(){ return _radius; }

		Circle(double radius, egui::Color_RGBA bgColor=egui::colors::Red, double bdWidth=0, egui::Color_RGBA bdColor=egui::colors::Transparent){
			_radius = radius;
			_backgroundColor = bgColor;
			_borderWidth = bdWidth;
			_borderColor = bdColor;
		}
	private:
		void _draw(SDL_Renderer* __renderer) override {
			
		}

		double _radius{0};
	};
}