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

#include <cstddef>

namespace egui{
/// Base class for all UI elements.
/// Combines rendering, transformation and interaction capabilities.
class Widget : public drawable, public transformable, public interactable {
public:
    virtual ~Widget() = default;

    /// Gets the rendering layer of the widget.
    /// Higher values are rendered on top of lower ones.
    /// @return Layer index.
    constexpr std::size_t getLayerNumber() const { return _layerN; }

    /// Sets the rendering layer of the widget.
    /// Widgets with higher layer values are drawn above others.
    /// @param n Layer index.
    void setLayerNumber(const std::size_t n) { _layerN = n; }

protected:
    std::size_t _layerN{0};

    friend class Window;
};
}