/*
EGUI - Embedded Graphics Utility Interface
Copyright (c) 2026 Stefano Rando (randostefano39@proton.me)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required. 
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#pragma once
#include "EGUI_Widget.hpp"
#include "EGUI_InputSys.hpp"

#include <vector>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

namespace egui{
	class Window{
	public:
		void create(const std::string& title, 
					const Vector2D& size, 
					const Color_RGBA& bgColor=egui::colors::White);

		void update();
		void destroy();
		void assign(Widget& widget);
		void remove(Widget& widget);

		void setBackgroundColor(Color_RGBA color);
		bool isOpen() const;

		Window(	const std::string title,
				const Vector2D size,
				const Color_RGBA bgColor=egui::colors::White);
		Window();
		~Window();
	private:
		inline bool _checkWidgetsOrder() const;
		inline void _sortWidgets();

		SDL_Window* _sdlwin{nullptr};
		SDL_Renderer* _sdlrenderer{nullptr};

		std::vector<Widget*> _widgets;

		Color_RGBA _backgroundColor{egui::colors::White};

		bool _isOpen{false};

		size_t _lastTime{0};
	};
}