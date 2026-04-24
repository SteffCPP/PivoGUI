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

#include "PIVO_Dep.hpp"
#include "Systems/PIVO_TextureSys.hpp"

namespace pivo{
// === sizeable ===

Vector2D sizeable::getSize() const { return _size; }
void sizeable::setSize(const Vector2D& size){ _size = size; }

// === rotatable ===

void rotatable::setRotation(double deg){ _rotation = deg; }
double rotatable::getRotation() const{ return _rotation; }
bool rotatable::_hasRotation() const { return _rotation != 0.0; }

// === borderable ===

Color_RGBA borderable::getBorderColor() const { return _borderColor; }
void borderable::setBorderColor(const Color_RGBA& color) { _borderColor = color; }
		
void borderable::setBorderWidth(const float width){ _borderWidth = width; }
float borderable::getBorderWidth() const { return _borderWidth; }

// === drawable ===

Color_RGBA drawable::getColor() const { return _color; }
void drawable::setColor(const Color_RGBA& color) { _color = color; }

void drawable::toggleHide(const bool flag){ _hide = flag; }

// === interactable ===

const interactable::HoverContext& interactable::getHoverContext() const { return _hoverContext; }
bool interactable::isPressed() const { return _pressed; }

void interactable::_triggerClick() const { if (_onClick) _onClick(); }
void interactable::_triggerHover() const { if (_onHover) _onHover(); }
void interactable::_triggerEnter() const { if (_onEnter) _onEnter(); }
void interactable::_triggerLeave() const { if (_onLeave) _onLeave(); }
void interactable::_triggerRelease() const { if(_onRelease) _onRelease(); }

// === texturable ===

void texturable::assignImage(const Image img){ _img = img; _hasImage = true; }
void texturable::assignImage(const std::string& path){ _img.setPath(path); _hasImage = true; }
void texturable::removeImage(){ _hasImage = false; }

// === pivotable ===

pivotable::Pivot pivotable::getPivot() const { return _pivot; }
void pivotable::setPivot(const Pivot& pivot){ _pivot = pivot; }

// === positionable ===

Vector2D positionable::getPosition() const { return _pos; }
void positionable::setPosition(const Vector2D& pos) { _pos = pos; }

void positionable::move(const Vector2D& delta) { _pos = _pos + delta; }
}