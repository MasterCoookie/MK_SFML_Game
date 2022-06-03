#pragma once
#include "Player.h"
class LoadingScreen
{
public:
	LoadingScreen(std::shared_ptr<sf::RenderWindow> win, std::string playerOne, std::string playerTwo);
	Player* getPlayerOne();
	Player* getPlayerTwo();
	void loadPlayers();
	void update(int loadingPercent);
	void render();
private:
	void initText();
	void initTexture();
	std::shared_ptr<sf::RenderWindow> window;
	sf::Text text;
	sf::Font font;
	std::unique_ptr<sf::Texture> texture;
	sf::Sprite sprite;
	std::string playerOneName;
	std::string playerTwoName;
	Player* playerOne;
	Player* playerTwo;
};

