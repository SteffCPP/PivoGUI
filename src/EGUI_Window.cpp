#include "EGUI_Window.hpp"
#include "EGUI_SDL.cpp"

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>

namespace egui {
inline bool Window::_checkWidgetsOrder() const {
    if (_widgets.size() < 2){
        if(_widgets.at(0)->getLayerNumber() > _widgets.at(1)->getLayerNumber())
            return false;
    }
    for (std::size_t i=0; i < _widgets.size()-1; ++i) {
        if (_widgets.at(i)->getLayerNumber() > _widgets.at(i+1)->getLayerNumber())
            return false;
    }
    return true;
}
inline void Window::_sortWidgets(){
    std::sort(_widgets.begin(), _widgets.end(), [](const Widget* a, const Widget* b){
        return a->getLayerNumber() > b->getLayerNumber();
    });
}

void Window::create(const std::string& title, 
                    const Vector2D& size, 
                    const Color_RGBA& bgColor){
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

void Window::update(){
    if(!_win || !_renderer || !_isOpen) return;
    if(!_checkWidgetsOrder()) _sortWidgets();

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
						Hitbox hitboxRect = w->getHitbox();
						SDL_FRect rect{ hitboxRect.getPosition().X(), hitboxRect.getPosition().Y(), 
                                        hitboxRect.getSize().X(), hitboxRect.getSize().Y()};
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
    std::size_t widLayerN = widget.getLayerNumber();
    std::size_t i=0;

    if(_widgets.empty()){
        if (widLayerN == 0) widget.setLayerNumber(1);
        _widgets.push_back(&widget);
        return;
    }
    
    if (widLayerN == 0) {
        for (i=0; i<_widgets.size(); ++i) {
            if (_widgets[i]->getLayerNumber() != i+1) break;
        }
        widget.setLayerNumber(i + 1);
    } else {
        for (i=0; i<_widgets.size(); ++i) {
            if (_widgets[i]->getLayerNumber() > widLayerN) break;
        }
    }
    
    _widgets.insert(_widgets.begin() + i, &widget);
}

Window::Window(const std::string title,
               const Vector2D size,
               const Color_RGBA bgColor) {
    create(title, size, bgColor);
}

Window::~Window() {
    destroy();
}
}