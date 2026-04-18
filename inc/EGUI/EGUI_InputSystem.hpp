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

#include "EGUI_Dep.hpp"

#include <utility>
#include <unordered_map>

struct SDL_Window; 

namespace egui{
	enum class Key {
		A, B, C, D, E, F, G,
		H, I, J, K, L, M, N,
		O, P, Q, R, S, T, U,
		V, W, X, Y, Z,

		Num0, Num1, Num2, Num3, Num4,
		Num5, Num6, Num7, Num8, Num9,

		ESCAPE,
		ENTER,
		SPACE,
		TAB,
		BACKSPACE,

		UP,
		DOWN,
		LEFT,
		RIGHT,

		LSHIFT, RSHIFT,
		LCTRL,  RCTRL,
		LALT,   RALT,

		F1, F2, F3, F4, F5, F6,
		F7, F8, F9, F10, F11, F12,

		UNKNOWN
	};
	enum class MouseButton{
		LEFT,
		MIDDLE,
		RIGHT,
		UNKNOWN
	};

    class Mouse{
    public:
		Vector2D getPosition() const { return _pos; }
		
		bool isButtonDown(MouseButton button) const { return _buttons.find(button)->second; }
		bool isButtonUp(MouseButton button) const { return !isButtonDown(button); }

		bool leftDown() const { return _buttons.find(MouseButton::LEFT)->second; }
		bool rightDown() const { return _buttons.find(MouseButton::MIDDLE)->second; }
		bool middleDown() const { return _buttons.find(MouseButton::RIGHT)->second; }

    private:
		void _setPosition(const Vector2D& pos){ _pos = pos; }
		void _setButtonDown(MouseButton button){ _buttons[button] = true; }
		void _setButtonUp(MouseButton button){ _buttons[button] = false; }

		Vector2D _pos{0, 0};
		std::unordered_map<MouseButton, bool> _buttons{{MouseButton::LEFT, false}, {MouseButton::MIDDLE, false}, {MouseButton::RIGHT, false}};

		friend class Input_System;
    };

    class Keyboard{
    public:
		bool isDown(Key key) const {
			auto it = _keys.find(key);
			return it != _keys.end() && it->second;
		}
		bool isUp(Key key) const {
			auto it = _keys.find(key);
			return it != _keys.end() && !it->second;
		}

		bool isPressed(Key key) const {
			return isDown(key) && !_wasDown(key);
		}

		bool isReleased(Key key) const {
			return !isDown(key) && _wasDown(key);
		}
    private:
		void _update(){
			_prevKeys = _keys;
		}

		bool _wasDown(Key key) const {
			auto it = _prevKeys.find(key);
			return it != _prevKeys.end() && it->second;
		}

		void _setKeyDown(Key key){
			_keys[key] = true;
		}
		void _setKeyUp(Key key){
			_keys[key] = false;
		}

		std::unordered_map<Key, bool> _keys;
		std::unordered_map<Key, bool> _prevKeys;

		friend class Input_System;
    };


	class Input_System{
	public:
		Mouse mouse;
		Keyboard keyboard;

		Input_System();
	private:
		Key _sdlkToKey(int sdlKey);
		MouseButton _sdlbToMouseButton(std::size_t button);
		void _update();

		bool _hasRequestedQuit() const  { return _requestQuit; }
		std::pair<bool, SDL_Window*> _hasRequestedWindowQuit() const { return _requestWindowQuit; }

		bool _requestQuit{false};
		std::pair<bool, SDL_Window*> _requestWindowQuit{false, nullptr};

		friend class Window;
	};
	extern Input_System defInputSys;
}