#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {800, 900});

	egui::Rectangle rect{{300, 300}, {50, 50}, egui::colors::Transparent};
	rect.setBorderColor(egui::colors::Red);
	rect.setBorderWidth(20);

	win.assign(rect);

	while(win.isOpen()){
		win.update();
	}

	return 0;
}