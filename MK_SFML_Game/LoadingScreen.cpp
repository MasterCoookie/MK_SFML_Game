#include <thread>
#include <future>
#include "LoadingScreen.h"
import AsyncLoading;

LoadingScreen::LoadingScreen(sf::RenderWindow* arg, std::string playerOne, std::string playerTwo)
{
	this->win = arg;
	this->playerOneName = playerOne;
	this->playerTwoName = playerTwo;
	this->initTexture();
	this->initText();
	this->sprite.setTexture(*(this->tex));
	
}

Player* LoadingScreen::getPlayerOne()
{
	return this->playerOne;
}

Player* LoadingScreen::getPlayerTwo()
{
	return this->playerTwo;
}

void LoadingScreen::loadPlayers()
{
	std::promise<Player*> promPlayerOne;
	std::future<Player*> loadedPlayerOne = promPlayerOne.get_future();
	std::promise<Player*> promPlayerTwo;
	std::future<Player*> loadedPlayerTwo = promPlayerTwo.get_future();
	std::thread th1(&LoadPlayer, std::ref(promPlayerOne), this->playerOneName);
	std::thread th2(&LoadPlayer, std::ref(promPlayerTwo), this->playerTwoName);
	DisplayLoadingStatus(this);
	th1.join();
	th2.join();
	this->playerOne = loadedPlayerOne.get();
	this->playerTwo = loadedPlayerTwo.get();
	
}

void LoadingScreen::update(int loadingPercent)
{
	this->text.setString(std::to_string(loadingPercent) + "%");
}

void LoadingScreen::render()
{
	this->win->clear();
	this->win->draw(this->sprite);
	this->win->draw(this->text);
	this->win->display();
}

void LoadingScreen::initText()
{

	if (!this->font.loadFromFile("./Textures/arial.ttf")) {
		std::cout << "Czcionka nie wczytana";
	}
	this->text.setFont(font); 
	this->text.setString("0%");
	this->text.setCharacterSize(24); 
	this->text.setFillColor(sf::Color::Red);
	this->text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->text.setPosition(0, 0);
}

void LoadingScreen::initTexture()
{
	this->tex = new sf::Texture;
	if (!this->tex->loadFromFile("./Textures/menu.png")) {
		std::cout << " ! LOADINGSCREEN: could not load menu img" << std::endl;
	}
}
