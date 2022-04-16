#include "GameEngine.h"

GameEngine::GameEngine() {
	//all inits
	this->initWindow();
	this->initVariables();
}

GameEngine::GameEngine(sf::RenderWindow* win)
{
	this->window = win;
	this->initVariables();
	this->initWorld("bcg.png");
}

GameEngine::~GameEngine() { 
	delete this->window;
}

void GameEngine::run() {
	//gameloop
	while (this->window->isOpen()) {
		this->pollEvents();
		this->update();
		this->render();
	}
}

std::vector<std::string> GameEngine::getResult()
{
	std::vector<std::string> vec={""};
	return vec;
}

void GameEngine::setInterSceneValues(std::vector<std::string>& vec)
{
	this->initPlayers(vec[0], vec[1]);
}

void GameEngine::initVariables() {
	
}

void GameEngine::initWorld(std::string textureName) {
	//load texture from file
	if (!this->worldBcgTex.loadFromFile("./Textures/" + textureName)) {
		std::cout << " ! ERR: GAMEENGINE::INITWORLD: could not load bcg img" << std::endl;
	}
	//set bcg to loaded texture
	this->worldBcg.setTexture(this->worldBcgTex);
}

void GameEngine::initPlayers(std::string p1charName, std::string p2charName) {
	//create players, based on character names
	this->player1 = new Player(p1charName);
	this->player2 = new Player(p2charName);

	//place players in the right position
	this->player1->setPosition(200.f, 800.f - this->player1->getBounds().height);
	this->player2->setPosition(1080.f - this->player2->getBounds().width, 800.f - this->player2->getBounds().height);
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

void GameEngine::update() {

}

void GameEngine::render() {
	//clear old render first
	this->window->clear();

	//draw stuf here
	this->renderWorld();

	this->player1->render(this->window);
	this->player2->render(this->window);


	//display stuff
	this->window->display();
}

void GameEngine::renderWorld() {
	this->window->draw(this->worldBcg);
}
