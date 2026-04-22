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

namespace pivo{
// === sizeable ===

Vector2D sizeable::getSize() const { return _size; }
void sizeable::setSize(const Vector2D& size){ _size = size; }

// === rotatable ===

void rotatable::setRotation(double deg){ _rotation = deg; }
double rotatable::getRotation() const{ return _rotation; }
bool rotatable::_hasRotation() const { return _rotation != 0.0; }

// === drawable ===

Color_RGBA drawable::getBackgroundColor() const { return _backgroundColor; }
Color_RGBA drawable::getBorderColor() const { return _borderColor; }

void drawable::setBackgroundColor(const Color_RGBA& color) { _backgroundColor = color; }
void drawable::setBorderColor(const Color_RGBA& color) { _borderColor = color; }
		
void drawable::setBorderWidth(const float width){ _borderWidth = width; }
float drawable::getBorderWidth() const { return _borderWidth; }

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

texturable::texturable(){}

// === transformable ===

Vector2D transformable::getPosition() const { return _pos; }
void transformable::setPosition(const Vector2D& pos) { _pos = pos; }

transformable::Pivot transformable::getPivot() const { return _pivot; }
void transformable::setPivot(const Pivot& pivot){ _pivot = pivot; }

void transformable::move(const Vector2D& delta) { _pos = _pos + delta; }

Vector2D transformable::_computePivotOffset() const {
	switch(_pivot){
		case Pivot::TOP_LEFT:     return {0, 0};
		case Pivot::TOP:          return {-_size.x / 2, 0};
		case Pivot::TOP_RIGHT:    return {-_size.x, 0};

		case Pivot::LEFT:         return {0, -_size.y / 2};
		case Pivot::CENTER:       return {-_size.x / 2, -_size.y / 2};
		case Pivot::RIGHT:        return {-_size.x, -_size.y / 2};

		case Pivot::BOTTOM_LEFT:  return {0, -_size.y};
		case Pivot::BOTTOM:       return {-_size.x / 2, -_size.y};
		case Pivot::BOTTOM_RIGHT: return {-_size.x, -_size.y};
	}
	return {0, 0};
}
}