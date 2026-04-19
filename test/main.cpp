#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {800, 900});

	egui::Rectangle rect{{300, 300}, {50, 50}, egui::colors::Transparent, 20.0f, egui::colors::Green};
	rect.setRotation(180.0);
	rect.assignImage("test/imgs/emoji.jpeg");
	egui::Circle circle{100.0f, {500, 500}, egui::colors::Transparent, 10.0f, egui::colors::Red};
	egui::Audio chopinFMinor("test/audio/chopinNocturneFMinor.mp3");
	chopinFMinor.play();
	win.assign(rect);
	win.assign(circle);
	egui::Keyboard::isDown(egui::Key::A);
	while(win.isOpen()){
		
		
		win.update();
	}

	return 0;
}