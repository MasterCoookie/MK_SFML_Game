#include <thread>
#include <future>
#include "LoadingScreen.h"
import AsyncLoading;

LoadingScreen::LoadingScreen(sf::RenderWindow* arg, std::string playerOne, std::string playerTwo)
{
	this->win = arg;
	this->playerOneName = playerOne;
	this->playerTwoName = playerTwo;
	this->text.setCharacterSize(50);
	this->text.setString("0%");
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
	std::thread th3(&DisplayLoadingStatus, this);
	th1.join();
	th2.join();
	th3.join();
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
	this->win->draw(this->text);
	this->win->display();
}
