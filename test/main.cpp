#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {800, 900});

	egui::Rectangle rect{{300, 300}, {50, 50}, egui::colors::Transparent, 20.0f, egui::colors::Red};
	egui::Circle circle{100.0f, {500, 500}, egui::colors::Transparent, 10.0f, egui::colors::Red};

	egui::Audio chopinFMinor("test/audio/chopinNocturneFMinor.mp3");
	chopinFMinor.play();
	win.assign(rect);
	win.assign(circle);

	while(win.isOpen()){
		if(egui::defInputSys.keyboard.isPressed(egui::Key::P)){
			chopinFMinor.isPaused() ? 
			chopinFMinor.resume() : chopinFMinor.pause();
		}else if(egui::defInputSys.keyboard.isPressed(egui::Key::T))
			egui::defAudioSys.setTime(chopinFMinor, egui::defAudioSys.getTime(chopinFMinor)+30000);
		

		win.update();
	}

	return 0;
}