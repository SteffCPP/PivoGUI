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

#include "EGUI_InputSys.hpp"
#include "EGUI_SDL.cpp"

namespace egui {

// =========================
//        MOUSE
// =========================

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

// === Input_Manager ===

Input_Manager::Input_Manager() {
    _requestQuit = false;
    _requestWindowQuit = {false, nullptr};

    Keyboard::_initKeys();
}
void Input_Manager::_update() {
    Keyboard::_update();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        switch (event.type) {

            case SDL_EVENT_QUIT:
                _requestQuit = true;
                break;

            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                _requestWindowQuit = {
                    true,
                    SDL_GetWindowFromID(event.window.windowID)
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

            default:
                break;
        }
    }
}

bool Input_Manager::_hasRequestedQuit() {
    return _requestQuit;
}
std::pair<bool, SDL_Window*> Input_Manager::_hasRequestedWindowQuit() {
    return _requestWindowQuit;
}
}