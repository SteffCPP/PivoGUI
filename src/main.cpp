#include <iostream>
#include "EGUI/EGUI.hpp"

int main(){
	egui::Window win;
	win.create("Finestra", {600, 600});

	egui::Rectangle rect({50, 50}, {100, 100}, egui::colors::Magenta);
	egui::Circle circle(100.0F, {400, 200}, egui::colors::Green, 10.0F, egui::colors::Black);

	rect.setOnEnter([](){std::cout << "Entrato nel quadrato. \n"; });
	rect.setOnLeave([](){std::cout << "Uscito dal quadrato. \n"; });
	rect.setOnClick([](){std::cout << "Cliccato il quadrato. \n"; });
	rect.setOnRelease([](){std::cout << "Lasciato il quadrato. \n"; });

	win.assign(rect);
	win.assign(circle);

	while(win.isOpen()){
		win.update();
	}
	
	return 0;
}