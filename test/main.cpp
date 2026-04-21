#include <iostream>
#include "PIVO/PIVO.hpp"

int main(){
	pivo::Window win("Finestra", {1080, 980});

	pivo::Rectangle rect{{300, 300}, {60, 60}, pivo::colors::Red};
	
	win.assign(rect);
	while(win.isOpen()){
		pivo::Input_Manager::update();
		win.update();
	}

	return 0;
}