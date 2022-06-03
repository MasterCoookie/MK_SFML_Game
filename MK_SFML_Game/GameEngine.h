#pragma once

#include "Player.h"
#include "Scene.h"
#include "LoadingScreen.h"
#include "HealthBar.h"
#include "Timer.h"
#include "WinCircle.h"
#include "GUIMessage.h"

#include "MatchManager.h"

class GameEngine : public Scene{
public:
	GameEngine();
	GameEngine(std::shared_ptr<sf::RenderWindow> win);
	~GameEngine();

	void updateInput();
	void moveGUIElements(float offsetX, float offsetY);

	void run() override;
	std::vector<std::string> getResult() override;
	void setInterSceneValues(std::vector<std::string>& vec) override;
private:
	

	//inits
	void initWindow();
	void initVariables();
	void initWorld(std::string textureName);
	void initPlayers(std::string p1charName, std::string p2charName);
	void initHealthBars(std::string name1, std::string name2);
	void initTimer();
	void initWinCircles();
	void initGUIMsg();
	void initPlayersPos();
	void pollEvents() override;

	//otehers
	void printDebug();
	void resetRound();


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

	std::unique_ptr<MatchManager> matchManager;


	//World
	sf::Texture worldBcgTex;
	sf::Sprite worldBcg;
	std::shared_ptr<sf::View> view;
	

	//Players
	std::shared_ptr<Player> player1;
	std::shared_ptr<Player> player2;
	
	//GUI
	std::unique_ptr<HealthBar> hbplayer1;
	std::unique_ptr<HealthBar> hbplayer2;
	std::unique_ptr<Timer> timerGUI;
	std::unique_ptr<WinCircle> wcplayer1;
	std::unique_ptr<WinCircle> wcplayer2;
	std::unique_ptr<GUIMessage> msg;
};