#pragma once
#include <functional>
#include "EGUI_Vector.hpp"
struct SDL_Renderer;
struct SDL_FRect;

namespace egui{
	class Widget{
	protected:
		enum class WidgetType{
			WIDGET,
			SHAPE,
			RECTANGLE
		};

		class Hitbox{
		public:
			constexpr Vector2D getPosition() const { return {_x, _y}; }
			constexpr Vector2D getSize() const { return {_w, _h}; }

			inline void setPosition(const Vector2D& pos){ _x = pos.X(); _y = pos.Y(); }
			inline void setSize(const Vector2D& size){ _w = size.X(); _h = size.Y(); }
			Hitbox(const Vector2D& size, const Vector2D& pos){
				_x = pos.X();
				_y = pos.Y();
				_w = size.X();
				_h = size.Y();
			}
			Hitbox(const float x, const float y, const float w, const float h){
				_x = x;
				_y = y;
				_w = w;
				_h = h;
			}
		private:
			float _x{0}, _y{0}, _w{0}, _h{0};
		};
	public:
		virtual ~Widget() = default;

		template<typename Func, typename... Args>
		void setOnClick(Func&& func, Args&&... args){
			_onClick = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

		constexpr WidgetType getType() const { return _type; }
		constexpr Vector2D getPosition() const { return _pos; }
		constexpr Hitbox getHitbox() const { return _hitbox; }
		constexpr size_t getLayerNumber() const { return _layerN; }

		inline void setPosition(const Vector2D& pos) { _pos = pos; _hitbox.setPosition(_pos); }
		inline void setLayerNumber(const size_t n) { _layerN = n; }
	protected:
		virtual void _draw(SDL_Renderer* __renderer) = 0;
		
		std::function<void()> _onClick;
		WidgetType _type{WidgetType::WIDGET};

		size_t _layerN{0};

		Vector2D _pos{0, 0};
		Hitbox _hitbox{{0, 0}, {0, 0}};

		friend class Window;
	};
}