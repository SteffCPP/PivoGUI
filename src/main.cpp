#include "EGUI/EGUI.hpp"
#include <iostream>

int main(){
	egui::Rectangle rect;
	rect.size() = {30, 30};
	rect.position() = {30, 50};
	rect.backgroundColor() = egui::colors::Red;
	rect.borderColor() = egui::colors::Black;
	rect.borderWidth() = 2;

	egui::Window win;
	win.create("Test", {500, 500});
	win.backgroundColor() = egui::colors::White;
	
	win.assign(rect);
	

	while(win.isOpen()){
		win.update();
	}

	return 0;
}