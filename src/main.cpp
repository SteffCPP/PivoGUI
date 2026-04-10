#include <iostream>
#include "EGUI/EGUI.hpp"

void onClickRect(){
	static std::size_t i=0;
	std::cout << "Premuto "<< ++i << "\n";
}

int main(){
	egui::Window win;
	win.create("Finestra", {300, 300});

	egui::Rectangle rect({50, 50}, {100, 100}, egui::colors::Magenta);
	rect.setOnClick(onClickRect);

	egui::Circle circle(100.0F, {200, 200}, egui::colors::Blue, 10.0F, egui::colors::Yellow);

	win.assign(rect);
	win.assign(circle);

	while(win.isOpen()){
		win.update();
	}

	return 0;
}