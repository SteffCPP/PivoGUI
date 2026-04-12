#include <iostream>
#include "EGUI/EGUI.hpp"

void onClickRect(){
	static std::size_t i=0;
	std::cout << "Premuto "<< ++i << "\n";
}

int main(){
	egui::Window win;
	win.create("Finestra", {600, 600});

	egui::Rectangle rect({50, 50}, {100, 100}, egui::colors::Magenta);

	egui::Circle circle(100.0F, {400, 200}, egui::colors::Green, 10.0F, egui::colors::Black);
	
	win.assign(rect);
	win.assign(circle);

	while(win.isOpen()){
		win.update();
	}

	return 0;
}