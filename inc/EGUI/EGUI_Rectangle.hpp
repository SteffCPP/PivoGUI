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

struct SDL_Rect;

namespace egui{
	class Rectangle : public Widget{
	public:
		virtual bool containsPoint(const Vector2D& point) const override {
			auto pos = getPosition();
			auto size = getSize();

			return point.x >= pos.x &&
				point.x <= pos.x + size.x &&
				point.y >= pos.y &&
				point.y <= pos.y + size.y;
		}

		Rectangle(	const Vector2D& size, 
					const Vector2D& pos, 
					const Color_RGBA& bgColor=egui::colors::Red, 
					const float bdWidth=0, 
					const Color_RGBA& bdColor=egui::colors::Transparent, 
					const float rotRad=0);
		Rectangle();
	private:
		void _draw(SDL_Renderer* __renderer) override;
	};
}