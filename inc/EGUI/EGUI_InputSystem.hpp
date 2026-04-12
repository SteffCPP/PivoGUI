#pragma once

#include "EGUI_Dep.hpp"

#include <utility>
#include <unordered_map>

struct SDL_Window; 

namespace egui{
	enum class Keys {
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
		bool isDown(Keys key) const {
			auto it = _keys.find(key);
			return it != _keys.end() && it->second;
		}
    private:
		void _setKeyDown(Keys key){
			_keys[key] = true;
		}	

		void _setKeyUp(Keys key){
			_keys[key] = false;
		}

		std::unordered_map<Keys, bool> _keys;

		friend class Input_System;
    };


	class Input_System{
	public:
		void assignMouse(Mouse& mouse){ _mouse = mouse; }
		void assignKeyboard(Keyboard& keyboard){ _keyboard = keyboard; }

		Mouse getMouse() const { return _mouse; }
		Keyboard getKeyboard() const { return _keyboard; }

		Input_System(){}
		Input_System(Mouse& mouse, Keyboard& keyboard){
			assignMouse(mouse);
			assignKeyboard(keyboard);
		}
	private:
		Keys _sdlkToKey(int sdlKey);
		MouseButton _sdlbToMouseButton(std::size_t button);
		void _update();

		bool _hasRequestedQuit() const  { return _requestQuit; }
		std::pair<bool, SDL_Window*> _hasRequestedWindowQuit() const { return _requestWindowQuit; }

		bool _requestQuit{false};
		std::pair<bool, SDL_Window*> _requestWindowQuit{false, nullptr};

		Mouse _mouse;
		Keyboard _keyboard;

		friend class Window;
	};
	extern Input_System defInputSystem;
}