#pragma once

#include "Player.h"
#include "Scene.h"
class GameEngine : public Scene{
public:
	GameEngine();
	GameEngine(sf::RenderWindow* win);
	~GameEngine();

	

	void run() override;
	std::string getResult() override;
private:
	sf::RenderWindow* window;

	//inits
	void initWindow();
	void initVariables();


	void pollEvents() override;


	//updates
	void update() override;



	// renders
	void render() override;

};