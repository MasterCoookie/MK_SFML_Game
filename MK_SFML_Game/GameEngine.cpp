#include "GameEngine.h"

GameEngine::GameEngine() {
	this->initWindow();
}

GameEngine::~GameEngine() {

}

void GameEngine::run() {
	//gameloop
	while (this->window->isOpen()) {
		this->pollEvents();
		this->update();
		this->render();
	}
}

void GameEngine::initWindow() {
	//initializes window with set params
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 960), "Mortul Kombet", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void GameEngine::pollEvents() {
	//eventy - exiting game
	sf::Event e;
	while (this->window->pollEvent(e)) {
		//red cross clicked
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		//escape button
		else if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void GameEngine::update()
{
}

void GameEngine::render() {
	//clear old render first
	this->window->clear();

	//draw stuf here


	//display stuff
	this->window->display();
}
