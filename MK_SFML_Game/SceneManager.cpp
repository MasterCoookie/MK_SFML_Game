#include "SceneManager.h"
SceneManager::SceneManager()
{
	this->initWindow();
	this->interSceneData = { "" };
	this->initScenesToExecute();
	
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::run()
{
	while (this->interSceneData[0] != "exit" && this->window->isOpen()) {
		std::ranges::for_each(scenesToExecute, [this](std::shared_ptr<Scene> s) {																		// for each <3 brachu 
			this->executeScene(s);									
			});
		if (this->interSceneData[0] != "rematch" && this->window->isOpen()) {
			this->initRematch();
		}
	}

}

void SceneManager::executeScene(std::shared_ptr<Scene> s)
{
	s->setInterSceneValues(this->interSceneData);
	s->run();
	this->interSceneData = s->getResult();
}

void SceneManager::initWindow()
{
	//initializes window with set params
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 960), "Patykovy Mordulec", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void SceneManager::initScenesToExecute()
{
	this->scenesToExecute.push_back(std::make_shared<SceneWelcomeScreen>(this->window));
	this->scenesToExecute.push_back(std::make_shared<SceneMenu>(this->window));
	this->scenesToExecute.push_back(std::make_shared<GameEngine>(this->window));

}

void SceneManager::initRematch()
{
	this->scenesToExecute.push_back(std::make_shared<SceneMenu>(this->window));
	this->scenesToExecute.push_back(std::make_shared <GameEngine>(this->window));
}

