#pragma once
#include "SDL3/SDL_render.h"
#include <functional>

namespace egui{
	class Widget{
	public:
		virtual ~Widget() = default;

		template<typename Func, typename... Args>
		void setOnClick(Func&& func, Args&&... args){
			_onClick = [func = std::forward<Func>(func),
						... args = std::forward<Args>(args)](){
				
				func(args...);
			};
		}

	private:
		virtual void _draw(SDL_Renderer* __renderer) = 0;
		void callClick(){
			_onClick();
		}
		
		std::function<void()> _onClick;
		friend class Window;
	};
}