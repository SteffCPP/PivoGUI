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

    // Rectangle of Label
    Vector2D offset = _computePivotOffset();
	Vector2D finalPos = _pos - offset;

	SDL_FRect drawRect{finalPos.x, finalPos.y, _size.x, _size.y};
	SDL_SetRenderDrawColor(__renderer, _borderColor.r, _borderColor.g, _borderColor.b, _borderColor.a);
	SDL_RenderFillRect(__renderer, &drawRect);

	drawRect.x+=_borderWidth;
	drawRect.y+=_borderWidth;
	drawRect.w-=_borderWidth*2;
	drawRect.h-=_borderWidth*2;
	SDL_SetRenderDrawColor(__renderer, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
	SDL_RenderFillRect(__renderer, &drawRect);

    // Text
    if(!text._ttffont){
        std::cerr << "Font not loaded.\n";
        return;
    }
    
    SDL_Color txtColor = {(std::uint8_t)text._color.r, (std::uint8_t)text._color.g, (std::uint8_t)text._color.b, (std::uint8_t)text._color.a};
    
    TTF_SetFontWrapAlignment(text._ttffont, (TTF_HorizontalAlignment)text._alignment);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid_Wrapped(text._ttffont, text._text.c_str(), text._text.size(), txtColor, text._size.x);
    if(!surfaceMessage){
        std::cerr << "TTF_RenderText_Solid error: " << SDL_GetError() << "\n";
        return;
    }
    
    SDL_Texture* message = SDL_CreateTextureFromSurface(__renderer, surfaceMessage);
    
    int w = surfaceMessage->w;
    int h = surfaceMessage->h;

    float availableWidth  = _size.x - (_borderWidth * 2) - (_padding * 2);
    float availableHeight = _size.y - (_borderWidth * 2) - (_padding * 2);

    float rectX = finalPos.x + _borderWidth + _padding;
    float rectY = finalPos.y + _borderWidth + _padding;

    float offsetX = 0.0f;
    float offsetY = 0.0f;

    switch(_textboxAlignment){
        case TextBoxAlignment::TOP_LEFT:
            break;

        case TextBoxAlignment::TOP:
            offsetX = (availableWidth - w) / 2.0f;
            break;

        case TextBoxAlignment::TOP_RIGHT:
            offsetX = (availableWidth - w);
            break;

        case TextBoxAlignment::LEFT:
            offsetY = (availableHeight - h) / 2.0f;
            break;

        case TextBoxAlignment::CENTER:
            offsetX = (availableWidth - w) / 2.0f;
            offsetY = (availableHeight - h) / 2.0f;
            break;

        case TextBoxAlignment::RIGHT:
            offsetX = (availableWidth - w);
            offsetY = (availableHeight - h) / 2.0f;
            break;

        case TextBoxAlignment::BOTTOM_LEFT:
            offsetY = (availableHeight - h);
            break;

        case TextBoxAlignment::BOTTOM:
            offsetX = (availableWidth - w) / 2.0f;
            offsetY = (availableHeight - h);
            break;

        case TextBoxAlignment::BOTTOM_RIGHT:
            offsetX = (availableWidth - w);
            offsetY = (availableHeight - h);
            break;
    }

    rectX += offsetX;
    rectY += offsetY;

    SDL_FRect rect = {rectX, rectY, (float)w, (float)h};
    if(!SDL_RenderTexture(__renderer, message, NULL, &rect)){
        std::cerr << "Error rendering texture of Text of TextLabel: " << SDL_GetError() << "\n";
        abort();
    }
    
    SDL_DestroySurface(surfaceMessage);
    SDL_DestroyTexture(message);

    SDL_SetRenderDrawBlendMode(__renderer, SDL_BLENDMODE_NONE);
}
}