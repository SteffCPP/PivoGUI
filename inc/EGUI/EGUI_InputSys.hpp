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
		static Vector2D getPosition();
		
		static bool isButtonDown(MouseButton button);
		static bool isButtonUp(MouseButton button);
		static bool leftDown();
		static bool rightDown();
		static bool middleDown();
    private:
		static void _setPosition(const Vector2D& pos);
		static void _setButtonDown(MouseButton button);
		static void _setButtonUp(MouseButton button);
		static MouseButton _sdlbToMouseButton(std::size_t button);

	 	static inline Vector2D _pos;
		static inline std::unordered_map<MouseButton, bool> _buttons{{MouseButton::LEFT, false}, {MouseButton::MIDDLE, false}, {MouseButton::RIGHT, false}};

		friend class Input_Manager;
    };

    class Keyboard{
    public:
		static bool isDown(Key key);
		static bool isUp(Key key);

		static bool isPressed(Key key);

		static bool isReleased(Key key);
    private:
		static Key _sdlkToKey(int sdlKey);
		static void _update();

		static bool _wasDown(Key key);

		static void _setKeyDown(Key key);
		static void _setKeyUp(Key key);

		static inline std::unordered_map<Key, bool> _keys;
		static inline std::unordered_map<Key, bool> _prevKeys;

		friend class Input_Manager;
    };


	class Input_Manager{
	public:
		Input_Manager();
	private:
		static void _update();

		static bool _hasRequestedQuit();
		static std::pair<bool, SDL_Window*> _hasRequestedWindowQuit();

		static inline bool _requestQuit{false};
		static inline std::pair<bool, SDL_Window*> _requestWindowQuit{false, nullptr};

		friend class Window;
	};
}