#include <iostream>
#include "EGUI/EGUI.hpp"

constexpr size_t WIN_H = 800;
constexpr size_t WIN_W = 900;
int main(){
	egui::Window win("Finestra", {WIN_W, WIN_H}, egui::colors::Black);

	egui::Circle ball(5.0f, {400, 400}, egui::colors::White);

	win.assign(ball);

	float deltaX=4.0f, deltaY=4.0f;
	while(win.isOpen()){
		win.update();

		if(ball.getPosition().y>=WIN_H) deltaY*=-1;
		if(ball.getPosition().y<=0) deltaY*=-1;

		if(ball.getPosition().x>=WIN_W) deltaX*=-1;
		if(ball.getPosition().x<=0) deltaX*=-1;


		ball.move({deltaX, deltaY});
	}
	return 0;
}