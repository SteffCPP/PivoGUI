#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "EGUI/EGUI.hpp"

constexpr size_t WIN_W = 1080;
constexpr size_t WIN_H = 900;
class Ball{
public:
	egui::Circle& getCircle(){ return _circle; }

	float getX(){ return _ballX; }
	float getY(){ return _ballY; }

	void invertDX() { _deltaX*=-1; }
	void invertDY() { _deltaY*=-1; }
	float& getDX() { return _deltaX; }
	float& getDY() { return _deltaY; }

	void reset(){
		int sign1 = rand()%2==0 ? 1 : -1;
		int sign2 = rand()%2==0 ? 1 : -1;
		_deltaX=3.0f*sign1;
		_deltaY=3.0f*sign2;

		_ballX=540; 
		_ballY=450;

		_circle.setPosition({_ballX, _ballY});
	}

	void update(){
		if(_ballY >= WIN_H || _ballY <= 0)
			invertDY();
		
		_circle.move({_deltaX, _deltaY});
		_ballX += _deltaX;
		_ballY += _deltaY;
	}
private:
	float _ballX=540, _ballY=450;
	float _deltaX=3.0f, _deltaY=3.0f;

	egui::Circle _circle{5.0f, {_ballX, _ballY}, egui::colors::White};
};

class Padel{
public:
	egui::Rectangle& getRect(){ return _rect; }

	float& getDY() { return _deltaY; }

	void moveUp(){
		_padelY -= _deltaY;

		if(_padelY<0)
			_padelY = 0;
		

		_rect.setPosition({_padelX, _padelY});
	}
	void moveDown(){ 
		_padelY += _deltaY;

		if(_padelY+_rect.getSize().y>WIN_H)
			_padelY = WIN_H-_rect.getSize().y;
		
		
		_rect.setPosition({_padelX, _padelY});
	}

	void reset(){
		_deltaY=3.5f;
		_padelY=450;

		_rect.setPosition({_padelX, _padelY});
	}

	Padel(float xPos) : _padelX(xPos) {}
private:
	float _padelX=100, _padelY=450;
	float _deltaY=3.5f;

	egui::Rectangle _rect{{10, 100}, {_padelX, _padelY}, egui::colors::White};
};

int main(){
	srand(time(NULL));

	unsigned int scoreP1=0, scoreP2=0;

	egui::Window window("Ponggg", {WIN_W, WIN_H}, egui::colors::Black);

	Ball ball;
	Padel padel1(100.0f), padel2(980.0f);

	std::vector<egui::Rectangle*> net;
	for(size_t i=0;i<15;i++){
		net.push_back(new egui::Rectangle((egui::Vector2D){15, (WIN_H/15)/2}, (egui::Vector2D){WIN_W/2, (float)i*(float)(WIN_H/15)}, egui::colors::White));
		window.assign(*net.at(i));
	}

	window.assign(ball.getCircle());
	window.assign(padel1.getRect());
	window.assign(padel2.getRect());

	bool waitForSpace = true;
	while(window.isOpen()){
		window.update();

		if(waitForSpace){
			if(egui::defInputSystem.getKeyboard().isDown(egui::Keys::SPACE)) waitForSpace=false;
			continue;
		}
		ball.update();

		auto padel1_Up = egui::defInputSystem.getKeyboard().isDown(egui::Keys::W);
		auto padel1_Down = egui::defInputSystem.getKeyboard().isDown(egui::Keys::S);
		auto padel2_Up = egui::defInputSystem.getKeyboard().isDown(egui::Keys::UP);
		auto padel2_Down = egui::defInputSystem.getKeyboard().isDown(egui::Keys::DOWN);

		auto ball_X1 = ball.getCircle().getPosition().x - ball.getCircle().getRadius();
		auto ball_X2 = ball.getCircle().getPosition().x + ball.getCircle().getRadius();
		auto ball_Y1 = ball.getCircle().getPosition().y - ball.getCircle().getRadius();
		auto ball_Y2 = ball.getCircle().getPosition().y + ball.getCircle().getRadius();

		auto padel1_X1 = padel1.getRect().getPosition().x;
		auto padel1_X2 = padel1.getRect().getPosition().x + padel1.getRect().getSize().x;
		auto padel1_Y1 = padel1.getRect().getPosition().y;
		auto padel1_Y2 = padel1.getRect().getPosition().y + padel1.getRect().getSize().y;

		auto padel2_X1 = padel2.getRect().getPosition().x;
		auto padel2_X2 = padel2.getRect().getPosition().x + padel2.getRect().getSize().x;
		auto padel2_Y1 = padel2.getRect().getPosition().y;
		auto padel2_Y2 = padel2.getRect().getPosition().y + padel2.getRect().getSize().y;


		// Collision player 1
		if(padel1_X1 < ball_X2 && padel1_X2 > ball_X1 &&
		   padel1_Y1 < ball_Y2 && padel1_Y2 > ball_Y1){
			
			ball.invertDX();

			if(ball.getDY()>0 && padel1_Up){ 
				ball.invertDY();
			}else if(ball.getDY()<0 && padel1_Down){
				ball.invertDY();
			}else{
				if(ball.getDX()<0) ball.getDX() -= 0.5f;
				else ball.getDX() += 0.5f;

				if(ball.getDY()<0) ball.getDY() -= 0.5f;
				else ball.getDY() += 0.5f;

				padel1.getDY() += 0.3f;
				padel2.getDY() += 0.3f;
			}
		}

		// Collision player 2
		if(padel2_X1 < ball_X2 && padel2_X2 > ball_X1 &&
		   padel2_Y1 < ball_Y2 && padel2_Y2 > ball_Y1){
			
			ball.invertDX();

			if(ball.getDY()>0 && padel2_Up){ 
				ball.invertDY();
			}else if(ball.getDY()<0 && padel2_Down){
				ball.invertDY();
			}else{
				if(ball.getDX()<0) ball.getDX() -= 0.5f;
				else ball.getDX() += 0.5f;

				if(ball.getDY()<0) ball.getDY() -= 0.5f;
				else ball.getDY() += 0.5f;

				padel1.getDY() += 0.3f;
				padel2.getDY() += 0.3f;
			}
		}

		if(padel1_Up) padel1.moveUp();
		else if(padel1_Down) padel1.moveDown();

		if(padel2_Up) padel2.moveUp();
		else if(padel2_Down) padel2.moveDown();


		auto printScores = [scoreP1, scoreP2](){
			std::cout << "P1: " << scoreP1 << "; P2: " << scoreP2 << "\n";
		};
		// Point condition & Win Condition
		if(ball.getX()>=WIN_W){ 
			scoreP1++;
			printScores();

			padel1.reset();
			padel2.reset();
			ball.reset();
			waitForSpace = true;
		}
		else if(ball.getX()<=0){
			scoreP2++;
			printScores();

			padel1.reset();
			padel2.reset();
			ball.reset();
			waitForSpace = true;
		}

		if(scoreP1==10){
			std::cout << "\n===GAMEOVER!===\nIl P1 Vince!\n";
			window.destroy();
		}
		else if(scoreP2==10){
			std::cout << "\n===GAMEOVER!===\nIl P2 Vince!\n";
			window.destroy();
		}
	}

	return 0;
}