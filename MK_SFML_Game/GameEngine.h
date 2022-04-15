#pragma once

#include "Player.h"

class GameEngine {
public:
	GameEngine();
	GameEngine(sf::RenderWindow* win);
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