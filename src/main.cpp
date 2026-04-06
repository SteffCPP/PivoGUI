#include "SDL3/SDL.h"
#include "EGUI.hpp"
#include <iostream>

int main(){
	std::cout << "Hello World!" << "\n";

	egui::Rectangle rect;
	rect.setSize({300, 500});
	rect.setPosition({300, 200});
	rect.setBackgroundColor({255, 0, 0 , 254});

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	SDL_SetRenderDrawColor(renderer, rect.getBackgroundColor().getR(), rect.getBackgroundColor().getG(), rect.getBackgroundColor().getB(), rect.getBackgroundColor().getA());

	SDL_FRect sdlRect;
	sdlRect.x = rect.getPosition().getX();
	sdlRect.y = rect.getPosition().getY();
	sdlRect.w = rect.getSize().getX();
	sdlRect.h = rect.getSize().getY();
	SDL_RenderRect(renderer, &sdlRect);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}