#pragma once

#include "Player.h"
#include "Scene.h"
#include "LoadingScreen.h"
#include "HealthBar.h"
#include "Timer.h"
#include "WinCircle.h"
#include "MatchManager.h"

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
	void initHealthBars(std::string name1, std::string name2);
	void initTimer();
	void initWinCircles();
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
	
	void moveGUIElements(float offsetX, float offsetY);

	// renders
	void render() override;
	void renderWorld();

	MatchManager* matchManager;


	//World
	sf::Texture worldBcgTex;
	sf::Sprite worldBcg;
	sf::View* view;
	

	//Players
	Player* player1;
	Player* player2;
	
	//GUI
	HealthBar* hbplayer1;
	HealthBar* hbplayer2;
	Timer* timerGUI;
	WinCircle* wcplayer1;
	WinCircle* wcplayer2;
};