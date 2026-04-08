#include "EGUI_Window.hpp"

#include "SDL3/SDL.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace egui {
void Window::create(const std::string& title, 
                    const Vector2D& size, 
                    const Color_RGBA& bgColor) {
    if (_isOpen || _win) return;

    // Inizializza SDL solo se non già fatto
    if (SDL_WasInit(0) == 0) {
        if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != true) {
            std::cerr << "Couldn't initialize SDL3: " << SDL_GetError() << "\n";
            return;
        }
    }

    // Crea finestra e renderer
    if (!SDL_CreateWindowAndRenderer(
			title.c_str(),
            static_cast<int>(size.X()),
            static_cast<int>(size.Y()),
            SDL_WINDOW_RESIZABLE,
            &_win,
            &_renderer)) {
        std::cerr << "Couldn't create window/renderer: " << SDL_GetError() << "\n";
        return;
    }

    _backgroundColor = bgColor;
    _isOpen = true;
}

void Window::update() {
    if (!_win || !_renderer || !_isOpen) return;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:{
				_isOpen = false;
			} break;
                
			case SDL_EVENT_MOUSE_BUTTON_DOWN:{
				if(event.button.button == SDL_BUTTON_LEFT){
					SDL_FPoint mousePos = { event.button.x, event.button.y };

					for(const auto& w : _widgets){
						Widget::Hitbox::FRect hitboxRect = w->getHitbox().getRect();
						SDL_FRect rect{ hitboxRect.x, hitboxRect.y, hitboxRect.w, hitboxRect.h};
						if(SDL_PointInRectFloat(&mousePos, &rect)){
							w->_onClick();
						}
					}
				}
			} break;
            default: break;
        }
    }

    SDL_SetRenderDrawColor(
        _renderer,
        _backgroundColor.R(),
        _backgroundColor.G(),
        _backgroundColor.B(),
        _backgroundColor.A()
    );
    SDL_RenderClear(_renderer);

    for (const auto& w : _widgets) {
        w->_draw(_renderer);
    }

    SDL_RenderPresent(_renderer);
    SDL_Delay(5);
}

void Window::destroy() {
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }

    if (_win) {
        SDL_DestroyWindow(_win);
        _win = nullptr;
    }

    _isOpen = false;
}

void Window::assign(Widget& widget) {
    _widgets.push_back(&widget);
}

Window::Window(const std::string title,
               const Vector2D size,
               const Color_RGBA bgColor) {
    create(title, size, bgColor);
}

Window::~Window() {
    destroy();
    SDL_Quit();
}
}