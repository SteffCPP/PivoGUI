#include "EGUI_Circle.hpp"
#include "EGUI_SDL.cpp"

namespace egui{
void Circle::_draw(SDL_Renderer* __renderer) {
	_drawFilledCircle(__renderer, _pos.X(), _pos.Y(), _radius , _borderColor);
	_drawFilledCircle(__renderer, _pos.X(), _pos.Y(), _radius - _borderWidth ,_backgroundColor);
}

inline void Circle::_drawFilledCircle(	SDL_Renderer* __renderer, 
								        const float __cx, 
								        const float __cy,
								        const float __radius,
								        const Color_RGBA& __color){
	SDL_SetRenderDrawColor(__renderer, __color.R(), __color.G(), __color.B(), __color.A());

	for(int dy = -__radius; dy <= __radius; dy++){
		int dx = (int)sqrt(__radius * __radius - dy * dy);

		int x1 = __cx - dx;
		int x2 = __cx + dx;
		int y = __cy + dy;

		SDL_RenderLine(__renderer, x1, y, x2, y);
	}
}
}
