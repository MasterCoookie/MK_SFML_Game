#include "SceneManager.h"
SceneManager::SceneManager()
{
	this->initWindow();
	this->interSceneData = { "" };
	this->initScenesToExecute();
	
}

SceneManager::~SceneManager()
{
	std::for_each(this->scenesToExecute.begin(), this->scenesToExecute.end(), [this](Scene* s) {																		// for each <3 brachu 
		delete s;
		});
}

void SceneManager::run()
{
	
		
	while (this->interSceneData[0] != "exit" && this->window->isOpen()) {
		std::for_each(this->scenesToExecute.begin(), this->scenesToExecute.end(), [this](Scene* s) {																		// for each <3 brachu 
			this->executeScene(s);									
			});
		if (this->interSceneData[0] != "rematch" && this->window->isOpen()) {
			this->initRematch();
		}
	}

}

void SceneManager::executeScene(Scene* s)
{
	s->setInterSceneValues(this->interSceneData);
	s->run();
	this->interSceneData = s->getResult();
}

void SceneManager::initWindow()
{
	//initializes window with set params
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 960), "Patykovy Mordulec", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void SceneManager::initScenesToExecute()
{
	this->scenesToExecute.push_back(new SceneLoadingScreen(this->window));
	this->scenesToExecute.push_back(new SceneMenu(this->window));
	this->scenesToExecute.push_back(new GameEngine(this->window));

}

void SceneManager::initRematch()
{
	this->scenesToExecute.push_back(new SceneMenu(this->window));
	this->scenesToExecute.push_back(new GameEngine(this->window));
}

