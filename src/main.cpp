#include <iostream>
#include "EGUI/EGUI.hpp"

void onClickRect(){
	static size_t i=0;
	std::cout << "Premuto "<< ++i << "\n";
}

int main(){
	egui::Window win("Test", {200, 200});

	egui::Rectangle rect({50, 50}, {100, 100}, egui::colors::Magenta);
	rect.setOnClick(onClickRect);

	win.assign(rect);

	while(win.isOpen()){
		win.update();
	}

	return 0;
}