#include <iostream>
#include "PIVO/PIVO.hpp"

int main(){
	pivo::Vector2D* winSize = new pivo::Vector2D(900, 800);
	pivo::Window win{"Pong!", winSize, pivo::colors::Gray};

	pivo::Rectangle pad1{{10, 100}, {100, winSize->y/2}, pivo::colors::White};
	pivo::Rectangle pad2{{10, 100}, {winSize->x-100, winSize->y/2}, pivo::colors::White};
	win.assign(pad1);
	win.assign(pad2);

	pivo::Circle ball{5.0f, {winSize->x/2, winSize->y/2}, pivo::colors::White};
	ball.setPivot(pivo::Circle::Pivot::CENTER);
	win.assign(ball);

	float ballDeltaX = 5;
	float ballDeltaY = 5;

	std::uint16_t score1=0, score2=0;

	auto reset = [&ball, &pad1, &pad2, winSize](){
		pad1.setPosition({100, winSize->y/2});
		pad2.setPosition({winSize->x-100, winSize->y/2});
		ball.setPosition({winSize->x/2, winSize->y/2});
	};

	while(win.isOpen()){
		pivo::Input_Manager::update();

		// Manage ball collision
		if(pad1.containsPoint(ball.getPosition())){
			ballDeltaX*=-1;
			if(ball.getPosition().y<=pad1.getPosition().y) ballDeltaY*=-1;
		}else if(pad2.containsPoint(ball.getPosition())){
			ballDeltaX*=-1;
			if(ball.getPosition().y<=pad2.getPosition().y) ballDeltaY*=-1;
		}else if(ball.getPosition().y<=0) ballDeltaY*=-1;
		else if(ball.getPosition().y>=winSize->y) ballDeltaY*=-1;

		ball.move({ballDeltaX, ballDeltaY});
		
		// Manage pads inputs
		// Pad1
		if(pivo::Keyboard::isDown(pivo::Key::W))
			if(pad1.getPosition().y>0) pad1.move({0, -7});
		if(pivo::Keyboard::isDown(pivo::Key::S))
			if(pad1.getPosition().y+pad1.getSize().y<winSize->y) pad1.move({0, 7});
		
		// Pad2
		if(pivo::Keyboard::isDown(pivo::Key::UP))
			if(pad2.getPosition().y>0) pad2.move({0, -7});
		if(pivo::Keyboard::isDown(pivo::Key::DOWN))
			if(pad2.getPosition().y+pad2.getSize().y<winSize->y) pad2.move({0, 7});

		// Check if point
		if(ball.getPosition().x<=0){
			score2++;
			reset();
		}else if(ball.getPosition().x>=winSize->x){
			score1++;
			reset();
		}
		
		
		win.update();
	}

	delete winSize;
	return 0;
}