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

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
	private:
		enum class Style{
			NORMAL 			= 0,
			BOLD 			= 1 << 0,
			ITALIC 			= 1 << 1,
			UNDERLINE 		= 1 << 2,
			STRIKETHROUGH 	= 1 << 3
		};
		enum class TextAlignment{
			INVALID = -1,
			LEFT,
			CENTER,
			RIGHT
		};
	public:
		void setText(const std::string& txt);
		std::string getText() const;

		void loadFont(const std::string& path, const float& size);

		void setSize(const float& size);
		float getSize() const;

		void setStyle(const Style& style);
		Style getStyle() const;

		void setColor(const Color_RGBA& color);
		Color_RGBA getColor() const;

		void setAlignment(Text::TextAlignment& align){ _alignment = align; }

		Text(){}
		Text(const std::string& text,
			const std::string& fontPath, 
			const float& size,
			const Color_RGBA& color=egui::colors::White);
		~Text();
	private:
		std::string _text{""};
		Color_RGBA _color{egui::colors::White};

		TTF_Text* _ttftext=nullptr;
		TTF_Font* _ttffont=nullptr;

		TextAlignment _alignment{TextAlignment::LEFT};

		friend class TextLabel;
		friend class TextLabelInput;
	};

	class TextLabel : public Widget{
	private:
		
	public:
		virtual bool containsPoint(const Vector2D& point) const override {
			return point.x >= _pos.x &&
				point.x <= _pos.x + _size.x &&
				point.y >= _pos.y &&
				point.y <= _pos.y + _size.y;
		}

		void setPadding(const float& padding){ _padding = padding; }
		Text text;
		TextLabel(){}
	private:
		void _draw(SDL_Renderer* __renderer) override;

		float _padding{10};
	};

	class TextLabelInput : public Widget{
	public:

	private:

	};
}