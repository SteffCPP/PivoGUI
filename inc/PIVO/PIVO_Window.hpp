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

#include "PIVO_Widget.hpp"
#include "Systems/PIVO_InputSys.hpp"

#include <vector>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

namespace pivo{
/// Core window system of the engine.
/// Manages SDL window, renderer and all registered widgets.
class Window {
public:
    /// Creates the window with given parameters.
    /// @param title Window title.
    /// @param size Window size in pixels (width, height).
    /// @param bgColor Background color (default = white).
    void create(const std::string& title,
                const Vector2D& size,
                const Color_RGBA& bgColor = colors::White);

    /// Main update loop.
    /// Handles rendering and widget updates.
    void update();

    /// Destroys the window and frees all resources.
    void destroy();

    /// Assigns a widget to be managed and rendered by the window.
    /// @param widget* Widget to add.
    void assign(Widget* widget);

    /// Removes a widget from the window.
    /// @param widget* Widget to remove.
    void remove(Widget* widget);

    /// Sets the background color of the window.
    /// @param color New background color.
    void setBackgroundColor(Color_RGBA color);

    /// Checks if the window is currently open.
    /// @return True if window is running.
    bool isOpen() const;

    /// Returns the size of the window.
    /// @return Vector2D.x = width; Vector2D.y = height
    Vector2D getSize() const;

    static double getDeltaT();

    /// Constructs a Window with parameters.
    /// @param title Window title.
    /// @param size Window size in pixels.
    /// @param bgColor Background color (default = white).
    Window(const std::string title,
           const Vector2D size,
           const Color_RGBA bgColor = colors::White);
    
    /// Constructs a Window with parameters.
    /// @param title Window title.
    /// @param size Window size in pixels. Peing a pointer means that the size will automatically update in your .cpp file.
    /// @param bgColor Background color (default = white).
    Window(const std::string title,
           Vector2D* size,
           const Color_RGBA bgColor = colors::White);

    Window();
    ~Window();

private:
    inline bool _checkWidgetsOrder() const;

    inline void _sortWidgets();

    SDL_Window* _sdlwin{nullptr};
    SDL_Renderer* _sdlrenderer{nullptr};

    std::vector<Widget*> _widgets;

    Color_RGBA _backgroundColor{colors::White};

    bool _isOpen{false};

    size_t _lastTime{0};

    static inline double _delta{0};

    Vector2D _size{0, 0};
    Vector2D* _connectedSize{nullptr};
};
}