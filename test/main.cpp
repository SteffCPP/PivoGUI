#include <iostream>
#include "PIVO/PIVO.hpp"

int main(){
	pivo::Window win("Finestra", {1080, 980}, {0, 200, 255});

	const float rectSizeX=50;
	const float rectSizeY=50;
	float rectPosX = 300;
	float rectPosY = 300;

	pivo::Rectangle rect{{rectSizeX, rectSizeY}, {rectPosX, rectPosY}};
	win.assign(rect);
	
	pivo::Rectangle ground{{1080, 300}, {0, 980-300}, pivo::colors::Green};
	win.assign(ground);
	
	pivo::Audio chopinNocturne("test/audio/chopinNocturneFMinor.mp3");
	pivo::Audio_Manager::load(chopinNocturne);
	pivo::Audio_Manager::play(chopinNocturne);

	int accel=0;
	bool canJump=true;
	while(win.isOpen()){
		pivo::Input_Manager::update();
		
		if(++accel>=40) accel=40;
		if(pivo::Keyboard::isPressed(pivo::Key::SPACE) && canJump){
			accel = -20;
			canJump = false;
		}
		rect.move({0, (float)accel});

		if(rect.getPosition().y+rectSizeY >= ground.getPosition().y){
			rect.setPosition({rectPosX, ground.getPosition().y-rectSizeY});
			canJump = true;
		}

		win.update();
	}

	return 0;
}