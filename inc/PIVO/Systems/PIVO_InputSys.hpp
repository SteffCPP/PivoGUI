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

#pragma once

#include "PIVO/PIVO_Dep.hpp"

#include <tuple>
#include <functional>
#include <unordered_map>

struct SDL_Window;

namespace pivo {
	
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
    static void _setPosition(const Vector2D& pos);

    static void _setButtonDown(MouseButton button);

    static void _setButtonUp(MouseButton button);

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

    static void toggleBindActivation(const std::string& name, const bool flag);

    /// Binds a key press directly to a function.
    /// The function must have a name so that you can activate/deactevate later.
    /// @param name Name of the function
    /// @param key Key to bind
    /// @param func Function to call
    /// @param args Parameters of the function
    template<typename Func, typename... Args>
    static void bindKeyPress(const std::string& name, const Key key, Func&& func, Args&&... args){
        Action newAction = {
            .func = [func = std::forward<Func>(func), ... args = std::forward<Args>(args)](){ func(args...);},
            .key = key,
            .trigger = Action::Trigger::PRESS,
        };
        _bindedActions[name] = newAction;
    }

    /// Binds a key being held down directly to a function.
    /// The function must have a name so that you can activate/deactevate later.
    /// @param name Name of the function
    /// @param key Key to bind
    /// @param func Function to call
    /// @param args Parameters of the function
    template<typename Func, typename... Args>
    static void bindKeyDown(const std::string& name, const Key key, Func&& func, Args&&... args){
        Action newAction = {
            .func = [func = std::forward<Func>(func), ... args = std::forward<Args>(args)](){ func(args...);},
            .key = key,
            .trigger = Action::Trigger::DOWN,
        };
        _bindedActions[name] = newAction;
    }

    /// Binds a key being released directly to a function.
    /// The function must have a name so that you can activate/deactevate later.
    /// @param name Name of the function
    /// @param key Key to bind
    /// @param func Function to call
    /// @param args Parameters of the function
    template<typename Func, typename... Args>
    static void bindKeyRelease(const std::string& name, const Key key, Func&& func, Args&&... args){
        Action newAction = {
            .func = [func = std::forward<Func>(func), ... args = std::forward<Args>(args)](){ func(args...);},
            .key = key,
            .trigger = Action::Trigger::RELEASE
        };
        _bindedActions[name] = newAction;
    }

private:
    struct Action{
        enum class Trigger{
            PRESS,
            RELEASE,
            DOWN
        };
        std::function<void()> func;
        Key key;
        Trigger trigger;
        bool active=true;
    };
    static void _initKeys();

    static Key _sdlkToKey(int sdlKey);

    static void _update();

    static bool _wasDown(Key key);

    static void _setKeyDown(Key key);

    static void _setKeyUp(Key key);

    static inline std::unordered_map<Key, bool> _keys{};
    static inline std::unordered_map<Key, bool> _prevKeys{};
    static inline std::unordered_map<std::string, Action> _bindedActions{};

    friend class Input_Manager;
	friend class Window;
};

class Input_Manager {
public:
    // Updates all input states (keyboard + mouse).
    static void update();
private:
    static bool _hasRequestedQuit();

    /// Checks if the size of the window has been changed.
    /// @return Touple made of: 
    /// 
    /// bool=Condition, uint32_t=ID, int=W, int=H
    static std::tuple<bool, std::uint32_t, int ,int> _hasChangedWindowSize();

    /// Checks if a specific window requested quit.
    /// @return Pair (requested, window pointer).
    static std::pair<bool, std::uint32_t> _hasRequestedWindowQuit();

    static void _triggerAction();

    static inline bool _requestQuit{false};
    static inline std::pair<bool, std::uint32_t> _requestWindowQuit{false, 0};
    static inline std::tuple<bool, std::uint32_t, int ,int> _windowResized{false, 0, 0, 0};

    friend class Window;
};
}