/*
EGUI - Easy Graphical User Interface
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

#include "EGUI_Widget.hpp"
#include <string>
#include <vector>

struct TTF_Font;
struct TTF_Text;
struct SDL_Renderer;

namespace egui{
	class Text{
	public:
		enum class Style{
			NORMAL 			= 0,
			BOLD 			= 1 << 0,
			ITALIC 			= 1 << 1,
			UNDERLINE 		= 1 << 2,
			STRIKETHROUGH 	= 1 << 3
		};
		enum class Alignment{
			INVALID = -1,
			LEFT,
			CENTER,
			RIGHT
		};
	public:
		void setText(const std::string& txt);
		std::string getText() const;
		void appendText(const std::string& txt);

		void loadFont(const std::string& path, const float& size);

		void setFontSize(const float& size);
		float getFontSize() const;

		void setStyle(const Style& style, const bool& flag);
		Style getStyle() const;

		void setColor(const Color_RGBA& color);
		Color_RGBA getColor() const;

		void setSize(const Vector2D& size){ _size = size; }
		Vector2D getSize() const { return _size; }

		void setAlignment(Text::Alignment align){ _alignment = align; }

		Text(){}
		Text(const std::string& text,
			const std::string& fontPath, 
			const float& size,
			const Color_RGBA& color=egui::colors::White);
		~Text();
	private:
		Vector2D _size{0, 0};
		std::string _text{""};
		Color_RGBA _color{egui::colors::White};
		short _styles;

		TTF_Text* _ttftext=nullptr;
		TTF_Font* _ttffont=nullptr;

		Alignment _alignment{Alignment::LEFT};

		friend class TextLabel;
		friend class TextLabelInput;
	};

	class TextLabel : public Widget{
	public:
		enum class TextBoxAlignment{
			TOP_LEFT,
			TOP,
			TOP_RIGHT,
			LEFT,
			CENTER,
			RIGHT,
			BOTTOM_LEFT,
			BOTTOM,
			BOTTOM_RIGHT
		};

		virtual bool containsPoint(const Vector2D& point) const override {
			return point.x >= _pos.x &&
				point.x <= _pos.x + _size.x &&
				point.y >= _pos.y &&
				point.y <= _pos.y + _size.y;
		}

		void setPadding(const float& padding){ _padding = padding; }

		void setTextboxAlignment(const TextBoxAlignment align){
			_textboxAlignment = align;
		}
		TextBoxAlignment getTextboxAlignment() const { return _textboxAlignment; }

		Text text;

		TextLabel(){}
		TextLabel(
			const Vector2D& position,
			const Vector2D& size,
			const std::string& textStr,
			const std::string& fontPath,
			const float& fontSize,
			const Color_RGBA& textColor = egui::colors::White)
		{
			_pos = position;
			_size = size;

			text.loadFont(fontPath, fontSize);
			text.setText(textStr);
			text.setColor(textColor);

			_textboxAlignment = TextBoxAlignment::CENTER;
		}
	private:
		void _draw(SDL_Renderer* __renderer) override;

		float _padding{10};
		TextBoxAlignment _textboxAlignment{TextBoxAlignment::CENTER};
	};

	class TextLabelInput : public Widget{
	public:

	private:
		
	};
}