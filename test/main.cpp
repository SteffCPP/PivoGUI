#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win("Finestra", {600, 600});

	while(win.isOpen()){
		win.update();
	}
	return 0;
}