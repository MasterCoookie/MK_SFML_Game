#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	void run();
private:
	sf::RenderWindow* window;

	//inits
	void initWindow();


	void pollEvents();


	//updates
	void update();



	// renders
	void render();

};