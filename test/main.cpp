#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {800, 900});

	egui::TextLabel label;
	label.setBackgroundColor(egui::colors::Gray);
	label.setSize({800, 800});
	label.setPosition({50, 50});
	label.text.loadFont("test/fonts/retro_gaming.ttf",100);
	label.text.setText("STAMPA\nCIAO");
	label.text.setColor(egui::colors::Cyan);

	win.assign(label);

	while(win.isOpen()){
		win.update();
	}

	return 0;
}