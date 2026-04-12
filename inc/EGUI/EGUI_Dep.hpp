#pragma once

#include "EGUI_Vector.hpp"
#include "EGUI_Math.hpp"
#include "EGUI_Color.hpp"

#include <functional>

struct SDL_Renderer;

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
			_rotationRadians = math::degToRad(deg);
		}
		inline void setRotationRadians(double rad){ 
			_rotationRadians = rad;
			_rotationDegrees = math::radToDeg(rad);
		}
		constexpr double getRotationDegrees() const { return _rotationDegrees; }
		constexpr double getRotationRadians() const { return _rotationRadians; }
	protected:
		double _rotationDegrees{0}, _rotationRadians{0};
	};

	class drawable{
	public:
		virtual ~drawable() = default;

		constexpr Color_RGBA getBackgroundColor() const { return _backgroundColor; }
		constexpr Color_RGBA getBorderColor() const { return _borderColor; }

		inline void setBackgroundColor(const Color_RGBA& color) { _backgroundColor = color; }
		inline void setBorderColor(const Color_RGBA& color) { _borderColor = color; }
	protected:
		virtual void _draw(SDL_Renderer* __renderer) = 0;

		Color_RGBA _backgroundColor{egui::colors::Black}, _borderColor{egui::colors::Transparent};
		float _borderWidth{0};
	};

	class interactable{
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
		void setOnExit(Func&& func, Args&&... args){
			_onExit = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}


	protected:
		std::function<void()> _onClick;
		std::function<void()> _onHover;
    	std::function<void()> _onEnter;
    	std::function<void()> _onExit;
	};

	class transformable: public sizeable, public rotatable{
	public:
		virtual ~transformable() = default;

		Vector2D getPosition() const { return _pos; }

		void setPosition(const Vector2D& pos) { _pos = pos; }

		void move(const Vector2D& delta) {
			_pos.x += delta.x;
			_pos.y += delta.y;
		}
	protected:
		Vector2D _pos{0, 0};
	};
}