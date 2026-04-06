#pragma once
#include "SDL3/SDL_render.h"

namespace egui{
	class Widget{
	public:
		virtual ~Widget() = default;
	private:
		virtual void _draw(SDL_Renderer* __renderer) = 0;
		
		friend class Window;
	};
}