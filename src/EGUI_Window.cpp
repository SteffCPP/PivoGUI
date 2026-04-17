/*
EGUI - Easy Graphical User Interface
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

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "EGUI_Window.hpp"
#include "EGUI_SDL.cpp"

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>

namespace egui {
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
    if (_isOpen || _win) return;

    if (SDL_WasInit(0) == 0) {
        if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
            std::cerr << "Couldn't initialize SDL3: " << SDL_GetError() << "\n";
            abort();
        }
        if(!TTF_Init()){ \
            std::cerr << "Couldn't initialize SDL3_ttf " << SDL_GetError() << "\n"; 
            abort(); 
        }
        if(!MIX_Init()){ \
            std::cerr << "Couldn't initialize SDL3_ttf " << SDL_GetError() << "\n"; 
            abort(); 
        }

        std::atexit([](){
            SDL_Quit();
            TTF_Quit();
            MIX_Quit();
        });
    }

    if (!SDL_CreateWindowAndRenderer(
			title.c_str(),
            static_cast<int>(size.x),
            static_cast<int>(size.y),
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

	defInputSystem._update();

	if(defInputSystem._hasRequestedQuit()) destroy();
	if(defInputSystem._hasRequestedWindowQuit().first && 
		defInputSystem._hasRequestedWindowQuit().second == _win) destroy();

	const Mouse& mouse = defInputSystem.mouse;
	const Keyboard& keyboard = defInputSystem.keyboard;

	Vector2D mousePos = mouse.getPosition();

	float _deltaTime = 0.016f;

	for (auto& w : _widgets) {
        bool inside = w->containsPoint(mousePos);

		w->_hoverContext.mousePos = mousePos;
        w->_hoverContext.leftButtonDown = mouse.leftDown();
		w->_hoverContext.rightButtonDown = mouse.rightDown();
		w->_hoverContext.middleButtonDown = mouse.middleDown();
        w->_hoverContext.hovering = inside;

        if (inside) {
			w->_hoverContext.timeHovered += _deltaTime;
            if (!w->_hovered) {
                w->_hovered = true;
                w->_triggerEnter();
            }

            w->_triggerHover();

            if (mouse.isButtonDown(MouseButton::LEFT) && !w->_pressed) {
                w->_pressed = true;
                w->_triggerClick();
            }else if(mouse.isButtonUp(MouseButton::LEFT) && w->_pressed){
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
    SDL_Delay(10);
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

void Window::remove(Widget& widget){
	_widgets.erase(
		std::remove_if(_widgets.begin(), _widgets.end(),
					[&](const Widget* ptr){
						return ptr == &widget;
					}),
		_widgets.end()
	);
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