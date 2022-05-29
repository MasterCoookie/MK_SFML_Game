#pragma once
#include "Player.h"
class LoadingScreen
{
public:
	LoadingScreen(sf::RenderWindow* arg, std::string playerOne, std::string playerTwo);
	Player* getPlayerOne();
	Player* getPlayerTwo();
	void loadPlayers();
	void update(int loadingPercent);
	void render();
private:
	void initText();
	void initTexture();
	sf::RenderWindow* win;
	sf::Text text;
	sf::Font font;
	sf::Texture* tex;
	sf::Sprite sprite;
	std::string playerOneName;
	std::string playerTwoName;
	Player* playerOne;
	Player* playerTwo;
};

