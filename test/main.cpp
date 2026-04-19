#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {1080, 980});

	egui::TextLabel label;
	label.setSize({600, 600});
	label.setPosition({200, 50});
	label.setRotation(40.0);
	label.setBackgroundColor(egui::colors::Gray);

	label.text.loadFont("test/fonts/retro_gaming.ttf", 30);
	label.text.setText("Ciao Mondo!");
	label.text.setColor(egui::colors::Cyan);
	
	win.assign(label);
	while(win.isOpen()){
		
		win.update();
	}

	return 0;
}