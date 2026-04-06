#include "SDL3/SDL.h"
#include "EGUI/EGUI.hpp"
#include <iostream>

int main(){
	std::cout << "Hello World!" << "\n";

	egui::Rectangle rect;
	rect.size() = {3, 5};
	rect.position() = {30, 50};
	rect.backgroundColor() = egui::colors::Red;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	SDL_SetRenderDrawColor(renderer, rect.backgroundColor().R(), rect.backgroundColor().G(), rect.backgroundColor().B(), rect.backgroundColor().A());

	SDL_FRect sdlRect;
	sdlRect.x = rect.position().X();
	sdlRect.y = rect.position().Y();
	sdlRect.w = rect.position().X();
	sdlRect.h = rect.position().Y();
	SDL_RenderRect(renderer, &sdlRect);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}