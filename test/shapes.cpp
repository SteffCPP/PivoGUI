#include <iostream>
#include "PIVO/PIVO.hpp"

int main(){
	pivo::Window win("Finestra", {1080, 900}, pivo::colors::Gray);

	pivo::Audio chopinNocturne("test/audio/chopinNocturneFMinor.mp3");
	chopinNocturne.play();

	// === Shapes ===

	pivo::Rectangle rect{{50, 50}, {50, 50}, pivo::colors::White};
	win.assign(rect);

	pivo::Ellipse ell({300, 200}, {200, 110}, pivo::colors::White);
	win.assign(ell);
	
	pivo::Triangle triangle{{400, 500}, {600, 700}, {800, 800}, pivo::colors::White};
	win.assign(triangle);

	pivo::Circle circle{40.0f, {300, 800}, pivo::colors::White};
	win.assign(circle);

	pivo::TextLabel label;
	label.text.loadFont("test/fonts/retro_gaming.ttf", 30);
	label.text.setText("Hello World!");
	label.text.setColor(pivo::colors::Gray);
	label.setPosition({700, 40});
	label.setSize({300, 100});
	label.setColor(pivo::colors::White);
	win.assign(label);

	pivo::Line line{{1000, 300}, {980, 700}, pivo::colors::White};
	win.assign(line);
	

	while(win.isOpen()){
		pivo::Input_Manager::update();

		if(pivo::Keyboard::isPressed(pivo::Key::UP)) chopinNocturne.changeVolume(0.1);
		else if(pivo::Keyboard::isPressed(pivo::Key::DOWN)) chopinNocturne.changeVolume(-0.1);

		win.update();
	}

	return 0;
}