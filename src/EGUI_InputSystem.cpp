#include "EGUI_InputSystem.hpp"
#include "EGUI_SDL.cpp"

namespace egui{
	Input_System defInputSystem;

Keys Input_System::_sdlkToKey(int sdlKey){
	using namespace egui;

	switch (sdlKey) {
		case SDLK_A: return Keys::A;
		case SDLK_B: return Keys::B;
		case SDLK_C: return Keys::C;
		case SDLK_D: return Keys::D;
		case SDLK_E: return Keys::E;
		case SDLK_F: return Keys::F;
		case SDLK_G: return Keys::G;
		case SDLK_H: return Keys::H;
		case SDLK_I: return Keys::I;
		case SDLK_J: return Keys::J;
		case SDLK_K: return Keys::K;
		case SDLK_L: return Keys::L;
		case SDLK_M: return Keys::M;
		case SDLK_N: return Keys::N;
		case SDLK_O: return Keys::O;
		case SDLK_P: return Keys::P;
		case SDLK_Q: return Keys::Q;
		case SDLK_R: return Keys::R;
		case SDLK_S: return Keys::S;
		case SDLK_T: return Keys::T;
		case SDLK_U: return Keys::U;
		case SDLK_V: return Keys::V;
		case SDLK_W: return Keys::W;
		case SDLK_X: return Keys::X;
		case SDLK_Y: return Keys::Y;
		case SDLK_Z: return Keys::Z;

		case SDLK_0: return Keys::Num0;
		case SDLK_1: return Keys::Num1;
		case SDLK_2: return Keys::Num2;
		case SDLK_3: return Keys::Num3;
		case SDLK_4: return Keys::Num4;
		case SDLK_5: return Keys::Num5;
		case SDLK_6: return Keys::Num6;
		case SDLK_7: return Keys::Num7;
		case SDLK_8: return Keys::Num8;
		case SDLK_9: return Keys::Num9;

		case SDLK_ESCAPE: return Keys::ESCAPE;
		case SDLK_RETURN: return Keys::ENTER;
		case SDLK_SPACE:  return Keys::SPACE;
		case SDLK_TAB:    return Keys::TAB;
		case SDLK_BACKSPACE: return Keys::BACKSPACE;

		case SDLK_UP:    return Keys::UP;
		case SDLK_DOWN:  return Keys::DOWN;
		case SDLK_LEFT:  return Keys::LEFT;
		case SDLK_RIGHT: return Keys::RIGHT;

		case SDLK_LSHIFT: return Keys::LSHIFT;
		case SDLK_RSHIFT: return Keys::RSHIFT;
		case SDLK_LCTRL:  return Keys::LCTRL;
		case SDLK_RCTRL:  return Keys::RCTRL;
		case SDLK_LALT:   return Keys::LALT;
		case SDLK_RALT:   return Keys::RALT;

		case SDLK_F1: return Keys::F1;
		case SDLK_F2: return Keys::F2;
		case SDLK_F3: return Keys::F3;
		case SDLK_F4: return Keys::F4;
		case SDLK_F5: return Keys::F5;
		case SDLK_F6: return Keys::F6;
		case SDLK_F7: return Keys::F7;
		case SDLK_F8: return Keys::F8;
		case SDLK_F9: return Keys::F9;
		case SDLK_F10: return Keys::F10;
		case SDLK_F11: return Keys::F11;
		case SDLK_F12: return Keys::F12;

		default: return Keys::UNKNOWN;
	}
}

MouseButton Input_System::_sdlbToMouseButton(std::size_t button){
	switch(button){
		case 1: return MouseButton::LEFT;
		case 2: return MouseButton::RIGHT;
		case 3: return MouseButton::MIDDLE;
		default: return MouseButton::UNKNOWN;
	}
	return MouseButton::UNKNOWN;
}

void Input_System::_update(){
	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
			// ---Window---

			case SDL_EVENT_QUIT:{
				_requestQuit = true;
			} break; 

			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:{
				_requestWindowQuit = {true, SDL_GetWindowFromID(event.window.windowID)};
			} break; 

			// ---Mouse---
		
            case SDL_EVENT_MOUSE_MOTION:{
				_mouse._setPosition({event.motion.x, event.motion.y});
			} break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN: {
				_mouse._setButtonDown(_sdlbToMouseButton(event.button.button));
			} break;

			case SDL_EVENT_MOUSE_BUTTON_UP: {
				_mouse._setButtonUp(_sdlbToMouseButton(event.button.button));
			} break;

			// ---Keyboard---

			case SDL_EVENT_KEY_DOWN: {
				_keyboard._setKeyDown(_sdlkToKey(event.key.key));
			} break;

			case SDL_EVENT_KEY_UP: {
				_keyboard._setKeyUp(_sdlkToKey(event.key.key));
			} break;

            default: break;
        }
    }
}
}