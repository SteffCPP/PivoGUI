#pragma once

#include "EGUI_Vector.hpp"
#include "EGUI_Math.hpp"
#include "EGUI_Hitbox.hpp"

struct SDL_Renderer;

namespace egui{
	class sizeable{
	public:
		constexpr virtual Vector2D getSize() const { return _size; }
		virtual void setSize(const Vector2D& size){ _size = size; }
	protected:
		Vector2D _size{0, 0};
	};

	class rotatable{
	public:
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

	class interactable{
	public:
		Hitbox getHitbox() const { return _hitbox; }

		template<typename Func, typename... Args>
		void setOnClick(Func&& func, Args&&... args){
			_onClick = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

	protected:
		std::function<void()> _onClick;

		Hitbox _hitbox{{0, 0}, {0, 0}};
	};

	class drawable{
	protected:
		virtual void _draw(SDL_Renderer* __renderer) = 0;
	};



	class transformable: public sizeable, public rotatable{};
}