/*
PivoGUI
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

#include "PIVO_Window.hpp"
#include "PIVO_InputSys.hpp"
#include "PIVO_SDL.cpp"
#include "PIVO_AudioSys.hpp"

#include <iostream>
#include <utility>

namespace pivo {
inline bool Window::_checkWidgetsOrder() const {
	if (_widgets.size() <= 1) return true;
    if (_widgets.size() == 2){
        if(_widgets.at(0)->getLayerNumber() > _widgets.at(1)->getLayerNumber())
			return false;
		
		return true;
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
    if (_isOpen || _sdlwin) return;

    if (SDL_WasInit(0) == 0) {
        if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
            std::cerr << "Couldn't initialize SDL3: " << SDL_GetError() << "\n";
            abort();
        }
        if(!TTF_Init()){ \
            std::cerr << "Couldn't initialize SDL3_ttf " << SDL_GetError() << "\n"; 
            abort(); 
        }
        Audio_Manager::_init();
    }

    if (!SDL_CreateWindowAndRenderer(
			title.c_str(),
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            SDL_WINDOW_RESIZABLE,
            &_sdlwin,
            &_sdlrenderer)) {
        std::cerr << "Couldn't create window/renderer: " << SDL_GetError() << "\n";
        return;
    }

	Keyboard::_initKeys();
    _lastTime = SDL_GetPerformanceCounter();
    _backgroundColor = bgColor;
    _isOpen = true;
}

Vector2D Window::getSize() const { return _size; }

void Window::update(){
    if(!_sdlwin || !_sdlrenderer || !_isOpen) return;
    if(!_checkWidgetsOrder()) _sortWidgets();

    int w, h;
    if(SDL_GetWindowSize(_sdlwin, &w, &h) && (w!=_size.x || h!=_size.y)){
        _size.x = w;
        _size.y = h;
    }

    const double targetFrameTime = 1000.0 / 60.0;
    Uint64 freq = SDL_GetPerformanceFrequency();
    Uint64 frameStart = SDL_GetPerformanceCounter();
    double delta = (frameStart - _lastTime) * 1000.0 / freq;
    _lastTime = frameStart;

    Audio_Manager::_update(delta);
    Input_Manager::update();

    const Mouse& mouse = Mouse();
    const Keyboard& keyboard = Keyboard();

    Vector2D mousePos = mouse.getPosition();

    for (auto& w : _widgets) {
        bool inside = w->containsPoint(mousePos);

        w->_hoverContext.mousePos = mousePos;
        w->_hoverContext.leftButtonDown = mouse.leftDown();
        w->_hoverContext.rightButtonDown = mouse.rightDown();
        w->_hoverContext.middleButtonDown = mouse.middleDown();
        w->_hoverContext.hovering = inside;

        if (inside) {
            w->_hoverContext.timeHovered += delta;

            if (!w->_hovered) {
                w->_hovered = true;
                w->_triggerEnter();
            }

            w->_triggerHover();

            if (mouse.isButtonDown(MouseButton::LEFT) && !w->_pressed) {
                w->_pressed = true;
                w->_triggerClick();
            } else if(mouse.isButtonUp(MouseButton::LEFT) && w->_pressed){
                w->_pressed = false;
                w->_triggerRelease();
            }
        } else {
            if (w->_hovered) {
                w->_hovered = false;
                w->_triggerLeave();
            }
            w->_pressed = false;
            w->_hoverContext.timeHovered = 0.0f;
        }
    }

    SDL_SetRenderDrawColor(
        _sdlrenderer,
        _backgroundColor.r,
        _backgroundColor.g,
        _backgroundColor.b,
        _backgroundColor.a
    );
    SDL_RenderClear(_sdlrenderer);

    for (const auto& w : _widgets) {
        w->_draw(_sdlrenderer);
    }

    SDL_RenderPresent(_sdlrenderer);

    Uint64 frameEnd = SDL_GetPerformanceCounter();
    double frameTime = (frameEnd - frameStart) * 1000.0 / freq;

    if(Input_Manager::_hasRequestedQuit()) { destroy(); return; }
    else if(Input_Manager::_hasRequestedWindowQuit().first && 
        Input_Manager::_hasRequestedWindowQuit().second == SDL_GetWindowID(_sdlwin)){ std::cout << "destroy"; destroy(); return; }

    if(frameTime < targetFrameTime){
        SDL_Delay(static_cast<Uint32>(targetFrameTime - frameTime));
    }
}

void Window::destroy() {
    if (_sdlrenderer) {
        SDL_DestroyRenderer(_sdlrenderer);
        _sdlrenderer = nullptr;
    }

    if (_sdlwin) {
        SDL_DestroyWindow(_sdlwin);
        _sdlwin = nullptr;
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

void Window::remove(Widget& widget){
	_widgets.erase(
		std::remove_if(_widgets.begin(), _widgets.end(),
					[&](const Widget* ptr){
						return ptr == &widget;
					}),
		_widgets.end()
	);
}

void Window::setBackgroundColor(Color_RGBA color){ _backgroundColor = color; }
bool Window::isOpen() const { return _isOpen; }

Window::Window(){}
Window::Window(const std::string title,
               const Vector2D size,
               const Color_RGBA bgColor) {
    create(title, size, bgColor);
}

Window::~Window() {
    destroy();
}
}