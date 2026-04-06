#pragma once
#include "EGUI_Rectangle.hpp"
#include "SDL3/SDL.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <vector>

namespace egui{
	class Window{
	public:
		void create(const std::string& title, 
					const Vector2D& size, 
					const Color_RGBA& bgColor=egui::colors::White)
		{
			if(_isOpen || _win) return;

			if(SDL_WasInit(0) == 0){ // If not initialized
				if(!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)){
					std::cerr << "Couldn't initialize SDL3: "<< SDL_GetError() << "\n";
					return;
				}
			}

			if (!SDL_CreateWindowAndRenderer(title.c_str(), size.X(), size.Y(), SDL_WINDOW_RESIZABLE, &_win, &_renderer)) {
				std::cerr << "Couldn't create window/renderer: " << SDL_GetError();
				return;
			}

			_backgroundColor = bgColor;
			_isOpen = true;
		}

		void update(){
			if(!_win || !_renderer || !_isOpen) return;

			SDL_Event event;
			while(SDL_PollEvent(&event)){
				if(event.type == SDL_EVENT_QUIT){
					_isOpen = false;
				}

				// Widgets management
			}

			SDL_SetRenderDrawColor(_renderer,
								   _backgroundColor.R(),
								   _backgroundColor.G(),
								   _backgroundColor.B(),
								   _backgroundColor.A());
			SDL_RenderClear(_renderer);

			for(auto& w : _widgets){
				w->_draw(_renderer);
			}

			SDL_RenderPresent(_renderer);
			SDL_Delay(10);
		}

		void destroy(){
			if(_renderer){
				SDL_DestroyRenderer(_renderer);
				_renderer = nullptr;
			}

			if(_win){
				SDL_DestroyWindow(_win);
				_win = nullptr;
			}

    		_isOpen = false;
		}

		void assign(Widget& widget){
			_widgets.push_back(&widget);
		}

		inline void setBackgroundColor(Color_RGBA color){ _backgroundColor = color; }
		bool isOpen() const { return _isOpen; }

		Window(	const std::string title,
				const Vector2D size,
				const Color_RGBA bgColor=egui::colors::White)
		{
			create(title, size, bgColor);
		}
		~Window(){
			destroy();
			SDL_Quit();
		}
	private:
		SDL_Window* _win=nullptr;
		SDL_Renderer* _renderer=nullptr;

		std::vector<Widget*> _widgets;

		Color_RGBA _backgroundColor{egui::colors::White};

		bool _isOpen=false;
	};
}