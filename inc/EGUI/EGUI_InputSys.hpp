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

namespace egui {
	
/// Represents keyboard keys used by the input system.
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
    LCTRL, RCTRL,
    LALT, RALT,

    F1, F2, F3, F4, F5, F6,
    F7, F8, F9, F10, F11, F12,

    UNKNOWN
};

/// Represents mouse buttons used by the input system.
enum class MouseButton {
    LEFT,     ///< Left mouse button.
    MIDDLE,   ///< Middle mouse button (wheel click).
    RIGHT,    ///< Right mouse button.
    UNKNOWN   ///< Undefined or unsupported button.
};

class Mouse {
public:

    /// Gets the current mouse position in screen coordinates.
    /// @return Mouse position as Vector2D.
    static Vector2D getPosition();

    /// Checks if a mouse button is currently pressed.
    /// @param button Mouse button to check.
    /// @return True if button is down.
    static bool isButtonDown(MouseButton button);

    /// Checks if a mouse button is currently released.
    /// @param button Mouse button to check.
    /// @return True if button is up.
    static bool isButtonUp(MouseButton button);

    /// Checks if left mouse button is pressed.
    /// @return True if left button is down.
    static bool leftDown();

    /// Checks if right mouse button is pressed.
    /// @return True if right button is down.
    static bool rightDown();

    /// Checks if middle mouse button is pressed.
    /// @return True if middle button is down.
    static bool middleDown();

private:
    /// Sets mouse position (internal use only).
    /// @param pos New mouse position.
    static void _setPosition(const Vector2D& pos);

    /// Marks a mouse button as pressed.
    /// @param button Button to set as down.
    static void _setButtonDown(MouseButton button);

    /// Marks a mouse button as released.
    /// @param button Button to set as up.
    static void _setButtonUp(MouseButton button);

    /// Converts SDL mouse button index to MouseButton enum.
    /// @param button SDL button index.
    /// @return Converted MouseButton.
    static MouseButton _sdlbToMouseButton(std::size_t button);

    static inline Vector2D _pos{};

    static inline std::unordered_map<MouseButton, bool> _buttons{
        {MouseButton::LEFT, false},
        {MouseButton::MIDDLE, false},
        {MouseButton::RIGHT, false}
    };

    friend class Input_Manager;
};

class Keyboard {
public:

    /// Checks if a key is currently pressed.
    /// @param key Key to check.
    /// @return True if key is down.
    static bool isDown(Key key);

    /// Checks if a key is currently released.
    /// @param key Key to check.
    /// @return True if key is up.
    static bool isUp(Key key);

    /// Checks if a key was just pressed this frame.
    /// @param key Key to check.
    /// @return True if key transitioned from up to down.
    static bool isPressed(Key key);

    /// Checks if a key was just released this frame.
    /// @param key Key to check.
    /// @return True if key transitioned from down to up.
    static bool isReleased(Key key);

private:
    /// Converts SDL keycode to internal Key enum.
    /// @param sdlKey SDL keycode.
    /// @return Converted Key enum.
    static Key _sdlkToKey(int sdlKey);

    /// Updates keyboard state (called each frame).
    static void _update();

    /// Checks previous frame state of a key.
    /// @param key Key to check.
    /// @return True if key was previously down.
    static bool _wasDown(Key key);

    /// Marks a key as pressed.
    /// @param key Key to set.
    static void _setKeyDown(Key key);

    /// Marks a key as released.
    /// @param key Key to set.
    static void _setKeyUp(Key key);

    static inline std::unordered_map<Key, bool> _keys{};
    static inline std::unordered_map<Key, bool> _prevKeys{};

    /// Initializes key map state.
    static void _initKeys();

    friend class Input_Manager;
};

class Input_Manager {
public:
    /// Constructs the input system.
    Input_Manager();
private:

    /// Updates all input states (keyboard + mouse).
    static void _update();

    /// Checks if the application requested global quit.
    /// @return True if quit was requested.
    static bool _hasRequestedQuit();

    /// Checks if a specific window requested quit.
    /// @return Pair (requested, window pointer).
    static std::pair<bool, SDL_Window*> _hasRequestedWindowQuit();

    static inline bool _requestQuit{false};
    static inline std::pair<bool, SDL_Window*> _requestWindowQuit{false, nullptr};

    friend class Window;
};
}