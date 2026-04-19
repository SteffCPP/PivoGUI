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

		virtual Vector2D getSize() const;
		virtual void setSize(const Vector2D& size);
	protected:
		Vector2D _size{0, 0};
	};

	class rotatable{
	public:
		virtual ~rotatable() = default;

		void setRotation(double deg);
		double getRotation() const;
	protected:
		bool _hasRotation() const;
		double _rotation{0};
	};

	class drawable{
	public:
		virtual ~drawable() = default;

	 	Color_RGBA getBackgroundColor() const;
		Color_RGBA getBorderColor() const;

		void setBackgroundColor(const Color_RGBA& color);
		void setBorderColor(const Color_RGBA& color);
		
		void setBorderWidth(const float width);
		float getBorderWidth() const;

		void setHide(const bool flag);

	protected:
		virtual void _draw(SDL_Renderer* __renderer) = 0;

		Color_RGBA _backgroundColor{egui::colors::Black}, _borderColor{egui::colors::Transparent};
		float _borderWidth{0};

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

		const HoverContext& getHoverContext() const;

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

	class texturable{
	public:
		void assignImage(const Image img);
		void assignImage(const std::string& path);
		void removeImage();
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

		Vector2D getPosition() const;
		void setPosition(const Vector2D& pos);

		Pivot getPivot() const;
		void setPivot(const Pivot& pivot);

		void move(const Vector2D& delta);
	protected:
		Vector2D _computePivotOffset() const;
		Pivot _pivot{Pivot::TOP_LEFT};
		
		Vector2D _pos{0, 0};
	};
}