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
			struct FRect{
				float x{0}, y{0}, w{0}, h{0};
			};
			constexpr FRect getRect() const { return _rect; }

			inline void setPosition(const Vector2D& pos){ 
				_rect.x = pos.X();
				_rect.y = pos.Y();
			}
			inline void setSize(const Vector2D& size){
				_rect.w = size.X();
				_rect.h = size.Y();
			}
			Hitbox(const Vector2D& size, const Vector2D& pos){
				_rect.x = pos.X();
				_rect.y = pos.Y();
				_rect.w = size.X();
				_rect.h = size.Y();
			}
		private:
			FRect _rect;
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
		constexpr Vector2D getSize() const { return _size; }
		constexpr Hitbox getHitbox() const { return _hitbox; }

		inline void setSize(const Vector2D& size) { _size = size; _hitbox.setSize(_size); }
		inline void setPosition(const Vector2D& pos) { _pos = pos; _hitbox.setPosition(_pos); }
	protected:
		virtual void _draw(SDL_Renderer* __renderer) = 0;
		
		std::function<void()> _onClick;
		WidgetType _type{WidgetType::WIDGET};

		Vector2D _pos{0, 0};
		Vector2D _size{0, 0};
		Hitbox _hitbox{{0, 0}, {0, 0}};

		friend class Window;
	};
}