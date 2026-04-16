#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {800, 900}, egui::colors::Black);
	egui::TextLabel label;

	label.setBackgroundColor(egui::colors::White);
	label.setSize({500, 500});
	label.setPosition({50, 50});
	label.text.loadFont("/home/stefano/Coding/EasyGUI/test/Kunaroh.ttf", 50);
	label.text.setText("Ciao Mondo!");
	label.text.setColor(egui::colors::Red);

	win.assign(label);

	while(win.isOpen()){




		win.update();
	}

	return 0;
}