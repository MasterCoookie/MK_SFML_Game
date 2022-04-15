#include "SceneManager.h"

SceneManager::SceneManager()
{
	this->initWindow();
}

SceneManager::~SceneManager()
{
	this->deleteWindow();
}

void SceneManager::run()
{
	GameEngine game(this->window);
	game.run();
}

void SceneManager::initWindow()
{
	//initializes window with set params
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 960), "Mortul Kombet", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void SceneManager::deleteWindow()
{
	delete window;
}
