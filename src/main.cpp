#include "EGUI/EGUI.hpp"
#include <iostream>

void printHello(){
	std::cout << "Hello World!";
}

int main(){
	egui::Window win("Finestra e Frocio", {900, 900}, egui::colors::Cyan);

	egui::Rectangle rect({30, 40}, {400, 400}, egui::colors::Red, 60, egui::colors::Blue);

	win.assign(rect);

	while(win.isOpen()){
		win.update();

		rect.setOnClick(printHello);
	}
	return 0;
}