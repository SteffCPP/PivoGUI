#pragma once
#include "EGUI_Widget.hpp"

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

		inline void setBackgroundColor(Color_RGBA color){ _backgroundColor = color; }
		inline bool isOpen() const {return _isOpen; }

		Window(	const std::string title,
				const Vector2D size,
				const Color_RGBA bgColor=egui::colors::White);
		Window(){}
		~Window();
	private:
		inline bool _checkWidgetsOrder() const;
		inline void _sortWidgets();

		SDL_Window* _win=nullptr;
		SDL_Renderer* _renderer=nullptr;

		std::vector<Widget*> _widgets;

		Color_RGBA _backgroundColor{egui::colors::White};

		bool _isOpen=false;
	};
}