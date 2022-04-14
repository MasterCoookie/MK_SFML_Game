#pragma once

#include "GameObject.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	

	void run();
private:
	sf::RenderWindow* window;

	//inits
	void initWindow();
	void initVariables();


	void pollEvents();


	//updates
	void update();



	// renders
	void render();

};