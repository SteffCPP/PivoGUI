#include "EGUI/EGUI.hpp"
#include <iostream>

int main(){
	egui::Rectangle rect;
	rect.setBackgroundColor(egui::colors::Green);
	rect.setSize({300, 300});

	egui::Window win("Test", {500, 500});
	
	win.assign(rect);
	
	while(win.isOpen()){
		win.update();
	}

	return 0;
}