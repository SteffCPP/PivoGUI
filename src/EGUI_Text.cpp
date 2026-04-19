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

#include "EGUI_Text.hpp"
#include "EGUI_SDL.cpp"

#include <iostream>

namespace egui{
#define FONT_NOT_LOADED_ERR \
if(_ttffont==nullptr){ \
    std::cerr << "Impossible to update size: Font not loaded.\n"; \
}

// === Text ===

Text::Text( const std::string& text,
			const std::string& fontPath, 
			const float& size,
			const Color_RGBA& color)
{ 	
	loadFont(fontPath, size); 
	setText(text);
	setColor(color);
}

Text::~Text(){
    TTF_CloseFont(_ttffont);
    _ttffont=nullptr;
}   

void Text::setStyle(const Style& style, const bool& flag){
    if(flag){
        _styles |= (short)style;
    }else{
        _styles &= ~(short)style;
    }
    
    TTF_SetFontStyle(_ttffont, _styles);
}
Text::Style Text::getStyle() const { 
    FONT_NOT_LOADED_ERR;
    return (Style)TTF_GetFontStyle(_ttffont); 
}

void Text::setText(const std::string& txt){ _text = txt; }
void Text::appendText(const std::string& txt){ _text += txt; }
std::string Text::getText() const { return _text; }

void Text::loadFont(const std::string& path, const float& size){ 
    _ttffont = TTF_OpenFont(path.c_str(), size);

    if(!_ttffont){
        std::cerr << "TTF_OpenFont error: " << SDL_GetError() << "\n";
        abort();
    }
}

void Text::setFontSize(const float& size){
    FONT_NOT_LOADED_ERR;
    TTF_SetFontSize(_ttffont, size); 
}
float Text::getFontSize() const {
    FONT_NOT_LOADED_ERR;
    return TTF_GetFontSize(_ttffont); 
}

void Text::setColor(const Color_RGBA& color){ _color = color; }
Color_RGBA Text::getColor() const { return _color; }

void Text::setSize(const Vector2D& size){ _size = size; }
Vector2D Text::getSize() const { return _size; }

void Text::setAlignment(Text::Alignment align){ _alignment = align; }



// === TextLabel ===

bool TextLabel::containsPoint(const Vector2D& point) const {
	return point.x >= _pos.x &&
		point.x <= _pos.x + _size.x &&
		point.y >= _pos.y &&
		point.y <= _pos.y + _size.y;
}

void TextLabel::setPadding(const float& padding){ _padding = padding; }

void TextLabel::setTextboxAlignment(const TextBoxAlignment align){
	_textboxAlignment = align;
}
TextLabel::TextBoxAlignment TextLabel::getTextboxAlignment() const { return _textboxAlignment; }

TextLabel::TextLabel(){}
TextLabel::TextLabel(
	const Vector2D& position,
	const Vector2D& size,
	const std::string& textStr,
	const std::string& fontPath,
	const float& fontSize,
	const Color_RGBA& textColor)
{
	_pos = position;
	_size = size;

	text.loadFont(fontPath, fontSize);
	text.setText(textStr);
	text.setColor(textColor);

	_textboxAlignment = TextBoxAlignment::CENTER;
}

void TextLabel::_draw(SDL_Renderer* __renderer){
    if(_hide) return;

    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_BLEND);

    // =========================
    // PIVOT + LABEL POSITION
    // =========================
    Vector2D topLeft = _pos + _computePivotOffset();

    SDL_FRect labelRect{
        topLeft.x,
        topLeft.y,
        _size.x,
        _size.y
    };

    SDL_FPoint rotationCenter{
        _pos.x - topLeft.x,
        _pos.y - topLeft.y
    };

    // =========================
    // LABEL TEXTURE
    // =========================
    SDL_Texture* labelTexture = SDL_CreateTexture(
        __renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        (int)_size.x,
        (int)_size.y
    );

    SDL_SetTextureBlendMode(labelTexture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(__renderer, labelTexture);
    SDL_SetRenderDrawColor(__renderer, 0,0,0,0);
    SDL_RenderClear(__renderer);

    SDL_SetRenderDrawColor(__renderer,
        _borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
    SDL_RenderFillRect(__renderer, nullptr);

    SDL_FRect innerRect{
        (float)_borderWidth,
        (float)_borderWidth,
        _size.x - _borderWidth * 2,
        _size.y - _borderWidth * 2
    };

    SDL_SetRenderDrawColor(__renderer,
        _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
    SDL_RenderFillRect(__renderer, &innerRect);

    SDL_SetRenderTarget(__renderer, nullptr);

    SDL_RenderTextureRotated(
        __renderer,
        labelTexture,
        nullptr,
        &labelRect,
        _rotation,
        &rotationCenter,
        SDL_FLIP_NONE
    );

    SDL_DestroyTexture(labelTexture);

    // =========================
    // TEXT (LOCAL SPACE FIRST)
    // =========================
    if(!text._ttffont) return;

    SDL_Color textColor{
        (Uint8)text._color.r,
        (Uint8)text._color.g,
        (Uint8)text._color.b,
        (Uint8)text._color.a
    };

    SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(
        text._ttffont,
        text._text.c_str(),
        text._text.size(),
        textColor,
        text._size.x
    );

    if(!textSurface) return;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(__renderer, textSurface);

    float textX = _borderWidth + _padding;
    float textY = _borderWidth + _padding;

    float availableWidth  = _size.x - (_borderWidth * 2) - (_padding * 2);
    float availableHeight = _size.y - (_borderWidth * 2) - (_padding * 2);

    switch(_textboxAlignment){
        case TextBoxAlignment::TOP:
            textX += (availableWidth - textSurface->w) / 2.0f;
            break;

        case TextBoxAlignment::TOP_RIGHT:
            textX += (availableWidth - textSurface->w);
            break;

        case TextBoxAlignment::LEFT:
            textY += (availableHeight - textSurface->h) / 2.0f;
            break;

        case TextBoxAlignment::CENTER:
            textX += (availableWidth - textSurface->w) / 2.0f;
            textY += (availableHeight - textSurface->h) / 2.0f;
            break;

        case TextBoxAlignment::RIGHT:
            textX += (availableWidth - textSurface->w);
            textY += (availableHeight - textSurface->h) / 2.0f;
            break;

        case TextBoxAlignment::BOTTOM_LEFT:
            textY += (availableHeight - textSurface->h);
            break;

        case TextBoxAlignment::BOTTOM:
            textX += (availableWidth - textSurface->w) / 2.0f;
            textY += (availableHeight - textSurface->h);
            break;

        case TextBoxAlignment::BOTTOM_RIGHT:
            textX += (availableWidth - textSurface->w);
            textY += (availableHeight - textSurface->h);
            break;

        default: break;
    }

    SDL_FRect textRect{
        topLeft.x + textX,
        topLeft.y + textY,
        (float)textSurface->w,
        (float)textSurface->h
    };

    SDL_RenderTextureRotated(
        __renderer,
        textTexture,
        nullptr,
        &textRect,
        _rotation,
        &rotationCenter,
        SDL_FLIP_NONE
    );

    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textTexture);

    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
}
}