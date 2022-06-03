#include <thread>
#include <future>
#include "LoadingScreen.h"
import AsyncLoading;

LoadingScreen::LoadingScreen(std::shared_ptr<sf::RenderWindow> win, std::string playerOne, std::string playerTwo)
{
	this->window = win;
	this->playerOneName = playerOne;
	this->playerTwoName = playerTwo;
	this->initTexture();
	this->initText();
	this->sprite.setTexture(*(this->texture));
	
}

std::shared_ptr<Player> LoadingScreen::getPlayerOne()
{
	return this->playerOne;
}

std::shared_ptr<Player> LoadingScreen::getPlayerTwo()
{
	return this->playerTwo;
}

void LoadingScreen::loadPlayers()
{
	std::promise<std::shared_ptr<Player>> promPlayerOne;
	std::future<std::shared_ptr<Player>> loadedPlayerOne = promPlayerOne.get_future();
	std::promise<std::shared_ptr<Player>> promPlayerTwo;
	std::future<std::shared_ptr<Player>> loadedPlayerTwo = promPlayerTwo.get_future();
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
	this->window->clear();
	this->window->draw(this->sprite);
	this->window->draw(this->text);
	this->window->display();
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
	this->texture = std::make_unique<sf::Texture>();
	if (!this->texture->loadFromFile("./Textures/menu.png")) {
		std::cout << " ! LOADINGSCREEN: could not load menu img" << std::endl;
	}
}
