#pragma once

#include "Player.h"
#include "Scene.h"
#include "LoadingScreen.h"
#include "HealthBar.h"
class GameEngine : public Scene{
public:
	GameEngine();
	GameEngine(sf::RenderWindow* win);
	~GameEngine();

	void updateInput();

	void run() override;
	std::vector<std::string> getResult() override;
	void setInterSceneValues(std::vector<std::string>& vec) override;
private:
	sf::RenderWindow* window;

	//inits
	void initWindow();
	void initVariables();
	void initWorld(std::string textureName);
	void initPlayers(std::string p1charName, std::string p2charName);
	void initHealthBars();


	void pollEvents() override;

	//otehers
	void printDebug();
	void endRound();


	//updates
	void update() override;
	
	void updatePlayersCross();
	void updatePlayersCollision();
	void updatePlayersScreenCollision();
	void updateAttacksCollision();
	void updateView();
	void updateTimer();
	

	// renders
	void render() override;
	void renderWorld();


	//World
	sf::Texture worldBcgTex;
	sf::Sprite worldBcg;
	sf::View* view;
	sf::Time roundTimer;
	sf::Time roundTimerMax;

	//Players
	Player* player1;
	Player* player2;
	
	//GUI
	HealthBar* hbplayer1;
	HealthBar* hbplayer2;
};