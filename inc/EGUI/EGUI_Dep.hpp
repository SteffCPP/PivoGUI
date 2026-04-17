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

#include "EGUI_Vector.hpp"
#include "EGUI_Math.hpp"
#include "EGUI_Color.hpp"
#include "EGUI_Image.hpp"

#include <functional>

struct SDL_Renderer;
struct SDL_Texture;

namespace egui{
	class sizeable{
	public:
		virtual ~sizeable() = default;

		virtual Vector2D getSize() const { return _size; }
		virtual void setSize(const Vector2D& size){ _size = size; }
	protected:
		Vector2D _size{0, 0};
	};

	class rotatable{
	public:
		virtual ~rotatable() = default;

		inline void setRotationDegrees(double deg){ 
			_rotationDegrees = deg; 
			_rotationRadians = egui::math::degToRad(deg);
		}
		inline void setRotationRadians(double rad){ 
			_rotationRadians = rad;
			_rotationDegrees = egui::math::radToDeg(rad);
		}
		constexpr double getRotationDegrees() const { return _rotationDegrees; }
		constexpr double getRotationRadians() const { return _rotationRadians; }
	protected:
		double _rotationDegrees{0}, _rotationRadians{0};
	};

	class drawable{
	public:
		virtual ~drawable() = default;

	 	Color_RGBA getBackgroundColor() const { return _backgroundColor; }
		Color_RGBA getBorderColor() const { return _borderColor; }

		void setBackgroundColor(const Color_RGBA& color) { _backgroundColor = color; }
		void setBorderColor(const Color_RGBA& color) { _borderColor = color; }
		
		void setBorderWidth(const float width){ _borderWidth = width; }
		float getBorderWidth() const { return _borderWidth; }

		void setHide(const bool flag){ _hide = flag; }

	protected:
		virtual void _draw(SDL_Renderer* __renderer) = 0;

		Color_RGBA _backgroundColor{egui::colors::Black}, _borderColor{egui::colors::Transparent};
		float _borderWidth{0};

		#define CHECK_IF_HIDE if(_hide) return;
		bool _hide{false};
	};

	class interactable{
	protected:
		struct HoverContext {
			Vector2D mousePos;
			bool leftButtonDown;
			bool rightButtonDown;
			bool middleButtonDown;
			bool hovering;
			float timeHovered;
		};
	public:
		virtual ~interactable() = default;
		
		virtual bool containsPoint(const Vector2D& point) const = 0;

		template<typename Func, typename... Args>
		void setOnClick(Func&& func, Args&&... args){
			_onClick = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

		template<typename Func, typename... Args>
		void setOnHover(Func&& func, Args&&... args){
			_onHover = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

		template<typename Func, typename... Args>
		void setOnEnter(Func&& func, Args&&... args){
			_onEnter = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

		template<typename Func, typename... Args>
		void setOnLeave(Func&& func, Args&&... args){
			_onLeave = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

		template<typename Func, typename... Args>
		void setOnRelease(Func&& func, Args&&... args){
			_onRelease = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

		const HoverContext& getHoverContext() const { return _hoverContext; }

   	 	bool isPressed() const { return _pressed; }
	protected:
		bool _hovered{false};
		bool _pressed{false};
		bool _isClicking{false};

		HoverContext _hoverContext;

		void _triggerClick() const { if (_onClick) _onClick(); }
		void _triggerHover() const { if (_onHover) _onHover(); }
		void _triggerEnter() const { if (_onEnter) _onEnter(); }
		void _triggerLeave() const { if (_onLeave) _onLeave(); }
		void _triggerRelease() const { if(_onRelease) _onRelease(); }
	private:
		std::function<void()> _onClick;
		std::function<void()> _onHover;
    	std::function<void()> _onEnter;
    	std::function<void()> _onLeave;
		std::function<void()> _onRelease;
	};

	class texturable{
	public:
		void assignImage(const Image img){ _img = img; _hasImage = true; }
		void assignImage(const std::string& path){ _img.setPath(path); _hasImage = true; }
		void removeImage(){ _hasImage = false; }
	protected:
		bool _hasImage{false};
		Image _img;
	};

	class transformable: public sizeable, public rotatable{
	protected:
		enum class Pivot{
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
	public:
		virtual ~transformable() = default;

		Vector2D getPosition() const { return _pos; }
		void setPosition(const Vector2D& pos) { _pos = pos; }

		Pivot getPivot() const { return _pivot; }
		void setPivot(const Pivot& pivot){ _pivot = pivot; }

		void move(const Vector2D& delta) { _pos = _pos + delta; }
	protected:
		Vector2D _computePivotOffset() const {
			switch(_pivot){
				case Pivot::TOP_LEFT:     return {0, 0};
				case Pivot::TOP:          return {_size.x / 2, 0};
				case Pivot::TOP_RIGHT:    return {_size.x, 0};

				case Pivot::LEFT:         return {0, _size.y / 2};
				case Pivot::CENTER:       return {_size.x / 2, _size.y / 2};
				case Pivot::RIGHT:        return {_size.x, _size.y / 2};

				case Pivot::BOTTOM_LEFT:  return {0, _size.y};
				case Pivot::BOTTOM:       return {_size.x / 2, _size.y};
				case Pivot::BOTTOM_RIGHT: return {_size.x, _size.y};
			}
			return {0, 0};
		}
		Pivot _pivot{Pivot::TOP_LEFT};
		
		Vector2D _pos{0, 0};
	};
}