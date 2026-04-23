#include <iostream>
#include "PIVO/PIVO.hpp"

int main(){
	pivo::Vector2D winSize{1080, 980};
	pivo::Color_RGBA winColor{0, 255, 255};
	pivo::Window win("Finestra", winSize, winColor);

	const float rectSizeX=50;
	const float rectSizeY=50;
	float rectPosX = 300;
	float rectPosY = 300;
	pivo::Rectangle rect{{rectSizeX, rectSizeY}, {rectPosX, rectPosY}};
	win.assign(rect);
	
	pivo::Rectangle ground{{winSize.x, 500}, {0, winSize.y-300}, pivo::colors::Green};
	win.assign(ground);

	//pivo::Audio chopinNocturne("test/audio/chopinNocturneFMinor.mp3");
	//chopinNocturne.play();

	pivo::Line line{{30, 40}, {600, 600}};
	win.assign(line);
	

	int accel=0;
	bool canJump=true;

	float nightTimer=60*1;

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
		
		if(--nightTimer<=0){
			winColor.b == 10 ? : winColor.b -= 1;
			winColor.g == 10 ? : winColor.g -= 1;
		}
		win.setBackgroundColor(winColor);

		if(win.getSize() != winSize){
			winSize = win.getSize();
			ground.setSize({winSize.x, 500});
		}

		win.update();
	}

	return 0;
}