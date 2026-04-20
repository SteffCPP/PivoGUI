#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {1080, 980});

	egui::Rectangle rect{{300, 300}, {60, 60}, egui::colors::Red};
	
	win.assign(rect);
	while(win.isOpen()){
		egui::Input_Manager::update();
		win.update();


	}

	return 0;
}