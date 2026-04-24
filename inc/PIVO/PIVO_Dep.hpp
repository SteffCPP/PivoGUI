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

#include "Primitives/PIVO_Vector.hpp"
#include "Primitives/PIVO_Color.hpp"
#include "PIVO_Math.hpp"
#include "Systems/PIVO_TextureSys.hpp"

#include <functional>

struct SDL_Renderer;
struct SDL_Texture;

namespace pivo{
class sizeable {
public:
    virtual ~sizeable() = default;

    /// Gets the size of the object.
    /// @return Size as a Vector2D (width, height).
    virtual Vector2D getSize() const;

    /// Sets the size of the object.
    /// @param size New size (width, height).
    virtual void setSize(const Vector2D& size);

protected:
    Vector2D _size{0, 0};
};

class rotatable {
public:
    virtual ~rotatable() = default;

    /// Sets the rotation angle in degrees.
    /// @param deg Rotation angle (degrees).
    virtual void setRotation(double deg);

    /// Gets the current rotation angle.
    /// @return Rotation in degrees.
    virtual double getRotation() const;

protected:
    /// Checks if rotation is enabled/meaningful for this object.
    /// @return True if rotation is applied.
    bool _hasRotation() const;

    double _rotation{0};
};

class borderable{
public:
    virtual ~borderable() = default;

    /// Gets the border color.
    /// @return Current border color.
    virtual Color_RGBA getBorderColor() const;

    /// Sets the border color.
    /// @param color New border color.
    virtual void setBorderColor(const Color_RGBA& color);

    /// Sets the border width.
    /// @param width Border thickness in pixels.
    virtual void setBorderWidth(const float width);

    /// Gets the border width.
    /// @return Border thickness in pixels.
    virtual float getBorderWidth() const;
protected:
    Color_RGBA _borderColor{colors::Transparent};
    float _borderWidth{0};
};

class drawable {
public:
    virtual ~drawable() = default;

    /// Gets the background color.
    /// @return Current color.
    virtual Color_RGBA getColor() const;

    /// Sets the background color.
    /// @param color New background color.
    virtual void setColor(const Color_RGBA& color);

    /// Hides or shows the object.
    /// @param flag True to hide, false to show.
    void toggleHide(const bool flag);

protected:
    /// Internal render function called by the UI system.
    /// @param __renderer SDL renderer context.
    virtual void _draw(SDL_Renderer* __renderer) = 0;

    Color_RGBA _color{colors::Black};

    bool _hide{false};
};

class interactable {
protected:
    /// Stores current mouse interaction state.
    struct HoverContext {
        Vector2D mousePos;          ///< Current mouse position.
        bool leftButtonDown;        ///< Left mouse button state.
        bool rightButtonDown;       ///< Right mouse button state.
        bool middleButtonDown;      ///< Middle mouse button state.
        bool hovering;              ///< True if mouse is over the object.
        float timeHovered;          ///< Time spent hovering.
    };

public:
    virtual ~interactable() = default;

    /// Checks if a point is inside the object.
    /// @param point Point in world space.
    /// @return True if point is inside.
    virtual bool containsPoint(const Vector2D& point) const = 0;

    /// Sets callback for click event.
    template<typename Func, typename... Args>
    void setOnClick(Func&& func, Args&&... args){
        _onClick = [func = std::forward<Func>(func),
                    ... args = std::forward<Args>(args)](){
                    
            func(args...);
        };
    }
    /// Sets callback for hover event.
    template<typename Func, typename... Args>
    void setOnHover(Func&& func, Args&&... args){
        _onHover = [func = std::forward<Func>(func),
                    ... args = std::forward<Args>(args)](){
                    
            func(args...);
        };
    }
    /// Sets callback for enter event.
    template<typename Func, typename... Args>
    void setOnEnter(Func&& func, Args&&... args){
        _onEnter = [func = std::forward<Func>(func),
                    ... args = std::forward<Args>(args)](){
                    
            func(args...);
        };
    }
    /// Sets callback for leave event.
    template<typename Func, typename... Args>
    void setOnLeave(Func&& func, Args&&... args){
        _onLeave = [func = std::forward<Func>(func),
                    ... args = std::forward<Args>(args)](){
                    
            func(args...);
        };
    }
    /// Sets callback for release event.
    template<typename Func, typename... Args>
    void setOnRelease(Func&& func, Args&&... args){
        _onRelease = [func = std::forward<Func>(func),
                    ... args = std::forward<Args>(args)](){
                    
            func(args...);
        };
    }
    /// Gets current hover context.
    /// @return Hover interaction state.
    const HoverContext& getHoverContext() const;

    /// Checks if object is currently pressed.
    /// @return True if pressed.
    bool isPressed() const;

protected:
    bool _hovered{false};
    bool _pressed{false};
    bool _isClicking{false};

    HoverContext _hoverContext;

    void _triggerClick() const;
    void _triggerHover() const;
    void _triggerEnter() const;
    void _triggerLeave() const;
    void _triggerRelease() const;

private:
    std::function<void()> _onClick;
    std::function<void()> _onHover;
    std::function<void()> _onEnter;
    std::function<void()> _onLeave;
    std::function<void()> _onRelease;
};

class texturable {
public:
    virtual ~texturable() = default;

    /// Assigns an image to the object.
    /// @param img Image resource to assign.
    virtual void assignImage(const Image img);

    /// Assigns an image from file path.
    /// @param path Path to image file.
    virtual void assignImage(const std::string& path);

    /// Removes the current image.
    virtual void removeImage();
protected:
    bool _hasImage{false};
    Image _img;
};

class pivotable{
public:
    virtual ~pivotable() = default;

    enum class Pivot {
        TOP,
        TOP_LEFT,
        TOP_RIGHT,
        LEFT,
        RIGHT,
        BOTTOM,
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        CENTER
    };

    /// Gets the current pivot type.
    /// @return Pivot mode.
    virtual Pivot getPivot() const;

    /// Sets the pivot type.
    /// @param pivot New pivot mode.
    virtual void setPivot(const Pivot& pivot);

protected:
    /// Computes pivot offset based on size and pivot mode.
    /// @return Offset vector.
    virtual Vector2D _computePivotOffset() const = 0;

    Pivot _pivot{Pivot::TOP_LEFT};
};

class positionable {
public:
    virtual ~positionable() = default;

    /// Gets the position of the object.
    /// @return Position in world space.
    virtual Vector2D getPosition() const;

    /// Sets the position of the object.
    /// @param pos New position.
    virtual void setPosition(const Vector2D& pos);

    /// Moves the object by delta.
    /// @param delta Movement offset.
    virtual void move(const Vector2D& delta);

protected:
    Vector2D _pos{0, 0};
};
}