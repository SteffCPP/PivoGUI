#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {800, 900});

	egui::Rectangle rect{{300, 300}, {50, 50}, egui::colors::Transparent};
	rect.setBorderColor(egui::colors::Red);
	rect.setBorderWidth(20);

	egui::Circle circle{100.0f, {500, 500}, egui::colors::Transparent};
	circle.setBorderColor(egui::colors::Red);
	circle.setBorderWidth(10);

	win.assign(rect);
	win.assign(circle);

	while(win.isOpen()){
		win.update();
	}

	return 0;
}