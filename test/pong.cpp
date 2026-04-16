#include <iostream>
#include "EGUI/EGUI.hpp"

constexpr size_t WIN_H = 800;
constexpr size_t WIN_W = 900;

void checkPadelPos(egui::Widget& pad){
	if(pad.getPosition().y + pad.getSize().y>=WIN_H) pad.setPosition({pad.getPosition().x, WIN_H - pad.getSize().y});
	if(pad.getPosition().y<=0) pad.setPosition({pad.getPosition().x, 0});
}

bool collisionPadBall(egui::Rectangle& pad, egui::Circle& ball){
	float cx = ball.getPosition().x + ball.getRadius();
	float cy = ball.getPosition().y + ball.getRadius();
	
	float closestX = std::clamp(cx, pad.getPosition().x, pad.getPosition().x + pad.getSize().x);
	float closestY = std::clamp(cy, pad.getPosition().y, pad.getPosition().y + pad.getSize().y);

	float dx = cx - closestX;
	float dy = cy - closestY;

	return (dx*dx + dy*dy) <= (ball.getRadius() * ball.getRadius());
}

int main(){
	egui::Window win("Finestra", {WIN_W, WIN_H}, egui::colors::Black);

	egui::Circle ball(5.0f, {400, 400}, egui::colors::White);
	egui::Rectangle pad1({10, 90}, {100, 400}, egui::colors::White);
	egui::Rectangle pad2({10, 90}, {800, 400}, egui::colors::White);

	win.assign(ball);
	win.assign(pad1);
	win.assign(pad2);

	float ballDeltaX=4.0f, ballDeltaY=4.0f;
	while(win.isOpen()){
		win.update();

		if(egui::defInputSystem.getKeyboard().isDown(egui::Keys::W)) pad1.move({0, -5});
		if(egui::defInputSystem.getKeyboard().isDown(egui::Keys::S)) pad1.move({0, 5});

		if(egui::defInputSystem.getKeyboard().isDown(egui::Keys::UP)) pad2.move({0, -5});
		if(egui::defInputSystem.getKeyboard().isDown(egui::Keys::DOWN)) pad2.move({0, 5});

		checkPadelPos(pad1);
		checkPadelPos(pad2);

		if(ball.getPosition().y>=WIN_H) ballDeltaY*=-1;
		if(ball.getPosition().y<=0) ballDeltaY*=-1;

		if(ball.getPosition().x>=WIN_W) ballDeltaX*=-1;
		if(ball.getPosition().x<=0) ballDeltaX*=-1;

		if(collisionPadBall(pad1, ball)) ballDeltaX*=-1;
		if(collisionPadBall(pad2, ball)) ballDeltaX*=-1;

		ball.move({ballDeltaX, ballDeltaY});
	}
	return 0;
}