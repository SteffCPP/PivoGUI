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

#include "PIVO_InputSys.hpp"
#include "PIVO_SDL.cpp"

namespace pivo {

// === Mouse === 

Vector2D Mouse::getPosition() {
    return _pos;
}
bool Mouse::isButtonDown(MouseButton button) {
    auto it = _buttons.find(button);
    return it != _buttons.end() && it->second;
}
bool Mouse::isButtonUp(MouseButton button) {
    return !isButtonDown(button);
}
bool Mouse::leftDown() {
    return isButtonDown(MouseButton::LEFT);
}
bool Mouse::rightDown() {
    return isButtonDown(MouseButton::RIGHT);
}
bool Mouse::middleDown() {
    return isButtonDown(MouseButton::MIDDLE);
}
void Mouse::_setPosition(const Vector2D& pos) {
    _pos = pos;
}
void Mouse::_setButtonDown(MouseButton button) {
    _buttons[button] = true;
}
void Mouse::_setButtonUp(MouseButton button) {
    _buttons[button] = false;
}
MouseButton Mouse::_sdlbToMouseButton(std::size_t button) {
    switch (button) {
        case 1: return MouseButton::LEFT;
        case 2: return MouseButton::RIGHT;
        case 3: return MouseButton::MIDDLE;
        default: return MouseButton::UNKNOWN;
    }
}

// === Keyboard ===

bool Keyboard::isDown(Key key) {
    auto it = _keys.find(key);
    return it != _keys.end() && it->second;
}
bool Keyboard::isUp(Key key) {
    return !isDown(key);
}
bool Keyboard::isPressed(Key key) {
    return isDown(key) && !_wasDown(key);
}
bool Keyboard::isReleased(Key key) {
    return !isDown(key) && _wasDown(key);
}
void Keyboard::_update() {
    _prevKeys = _keys;
}
bool Keyboard::_wasDown(Key key) {
    auto it = _prevKeys.find(key);
    return it != _prevKeys.end() && it->second;
}
void Keyboard::_setKeyDown(Key key) {
    _keys[key] = true;
}
void Keyboard::_setKeyUp(Key key) {
    _keys[key] = false;
}
void Keyboard::_initKeys() {
    for (int i = (int)Key::A; i <= (int)Key::F12; i++) {
        _keys[(Key)i] = false;
        _prevKeys[(Key)i] = false;
    }
}
Key Keyboard::_sdlkToKey(int sdlKey){ 
    using namespace pivo;
    switch (sdlKey) { 
        case SDLK_A: return Key::A; 
        case SDLK_B: return Key::B; 
        case SDLK_C: return Key::C; 
        case SDLK_D: return Key::D; 
        case SDLK_E: return Key::E; 
        case SDLK_F: return Key::F; 
        case SDLK_G: return Key::G; 
        case SDLK_H: return Key::H; 
        case SDLK_I: return Key::I; 
        case SDLK_J: return Key::J; 
        case SDLK_K: return Key::K; 
        case SDLK_L: return Key::L; 
        case SDLK_M: return Key::M; 
        case SDLK_N: return Key::N; 
        case SDLK_O: return Key::O; 
        case SDLK_P: return Key::P; 
        case SDLK_Q: return Key::Q; 
        case SDLK_R: return Key::R; 
        case SDLK_S: return Key::S; 
        case SDLK_T: return Key::T; 
        case SDLK_U: return Key::U; 
        case SDLK_V: return Key::V; 
        case SDLK_W: return Key::W; 
        case SDLK_X: return Key::X; 
        case SDLK_Y: return Key::Y; 
        case SDLK_Z: return Key::Z; 
        case SDLK_0: return Key::Num0; 
        case SDLK_1: return Key::Num1; 
        case SDLK_2: return Key::Num2; 
        case SDLK_3: return Key::Num3; 
        case SDLK_4: return Key::Num4; 
        case SDLK_5: return Key::Num5; 
        case SDLK_6: return Key::Num6; 
        case SDLK_7: return Key::Num7; 
        case SDLK_8: return Key::Num8; 
        case SDLK_9: return Key::Num9; 
        case SDLK_ESCAPE: return Key::ESCAPE; 
        case SDLK_RETURN: return Key::ENTER; 
        case SDLK_SPACE: return Key::SPACE; 
        case SDLK_TAB: return Key::TAB; 
        case SDLK_BACKSPACE: return Key::BACKSPACE; 
        case SDLK_UP: return Key::UP; 
        case SDLK_DOWN: return Key::DOWN; 
        case SDLK_LEFT: return Key::LEFT; 
        case SDLK_RIGHT: return Key::RIGHT; 
        case SDLK_LSHIFT: return Key::LSHIFT; 
        case SDLK_RSHIFT: return Key::RSHIFT; 
        case SDLK_LCTRL: return Key::LCTRL; 
        case SDLK_RCTRL: return Key::RCTRL; 
        case SDLK_LALT: return Key::LALT; 
        case SDLK_RALT: return Key::RALT; 
        case SDLK_F1: return Key::F1; 
        case SDLK_F2: return Key::F2; 
        case SDLK_F3: return Key::F3; 
        case SDLK_F4: return Key::F4; 
        case SDLK_F5: return Key::F5; 
        case SDLK_F6: return Key::F6; 
        case SDLK_F7: return Key::F7; 
        case SDLK_F8: return Key::F8; 
        case SDLK_F9: return Key::F9; 
        case SDLK_F10: return Key::F10; 
        case SDLK_F11: return Key::F11; 
        case SDLK_F12: return Key::F12; 
        default: return Key::UNKNOWN; 
    }
    return Key::UNKNOWN;
}

// === Input_Manager ===

void Input_Manager::update(){
    Keyboard::_update();

	_requestQuit = false;
    _requestWindowQuit = {false, 0};
    _windowResized = {false, 0, 0, 0};

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                _requestQuit = true;
                break;

            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                _requestWindowQuit = {
                    true,
                    event.window.windowID
                };
                break;

            case SDL_EVENT_MOUSE_MOTION:
                Mouse::_setPosition({event.motion.x, event.motion.y});
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                Mouse::_setButtonDown(
                    Mouse::_sdlbToMouseButton(event.button.button)
                );
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                Mouse::_setButtonUp(
                    Mouse::_sdlbToMouseButton(event.button.button)
                );
                break;

            case SDL_EVENT_KEY_DOWN:
                Keyboard::_setKeyDown(
                    Keyboard::_sdlkToKey(event.key.key)
                );
                break;

            case SDL_EVENT_KEY_UP:
                Keyboard::_setKeyUp(
                    Keyboard::_sdlkToKey(event.key.key)
                );
                break;

            case SDL_EVENT_WINDOW_RESIZED:
                _windowResized = {true, event.window.windowID, event.window.data1, event.window.data2};
                break;
            default:
                break;
        }
    }
}

bool Input_Manager::_hasRequestedQuit() {
    return _requestQuit;
}
std::pair<bool, std::uint32_t> Input_Manager::_hasRequestedWindowQuit() {
    return _requestWindowQuit;
}
std::tuple<bool, std::uint32_t, int ,int> Input_Manager::_hasChangedWindowSize(){
    return _windowResized;
}
}