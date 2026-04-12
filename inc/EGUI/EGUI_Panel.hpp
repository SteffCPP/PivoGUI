#pragma once

#include "EGUI_Dep.hpp"
#include "EGUI_Widget.hpp"

#include <vector>

namespace egui{
	class Panel : public Widget{
	public:
		
	private:
		virtual void _draw(SDL_Renderer* __renderer) override{}

		float _nextPosForShape{0};
	};
}