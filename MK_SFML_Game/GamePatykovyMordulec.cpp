#include "GamePatykovyMordulec.h"
GamePatykovyMordulec::GamePatykovyMordulec()
{
	this->initWindow();
	this->interSceneData = { "" };
	this->initScenesToExecute();
	
}

GamePatykovyMordulec::~GamePatykovyMordulec()
{
	
}

void GamePatykovyMordulec::run()
{
	while (this->interSceneData[0] != "exit" && this->window->isOpen()) {
		for (int i = 0; i < this->scenesToExecute.size(); i++) {
			this->executeScene(this->scenesToExecute[i]);
			//this->scenesToExecute.erase(this->scenesToExecute.begin());
		}
		if (this->interSceneData[0] == "F3" && this->window->isOpen()) {
			this->initRematch();
		}
		else if (this->interSceneData[0] == "F2" && this->window->isOpen()) {
			this->initRematchWithoutChange();
		}
	}

}

void GamePatykovyMordulec::executeScene(std::shared_ptr<Scene> s)
{
	s->setInterSceneValues(this->interSceneData);
	s->run();
	this->interSceneData = s->getResult();
	this->historyOfSceneData.push_back(this->interSceneData);
}

void GamePatykovyMordulec::initWindow()
{
	//initializes window with set params
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 960), "Patykovy Mordulec", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void GamePatykovyMordulec::initScenesToExecute()
{
	this->scenesToExecute.push_back(std::make_shared<SceneWelcomeScreen>(this->window));
	this->scenesToExecute.push_back(std::make_shared<SceneMenu>(this->window));
	this->scenesToExecute.push_back(std::make_shared<GameEngine>(this->window));

}

void GamePatykovyMordulec::initRematch()
{
	this->scenesToExecute.clear();
	this->scenesToExecute.push_back(std::make_shared<SceneMenu>(this->window));
	this->scenesToExecute.push_back(std::make_shared <GameEngine>(this->window));
}

void GamePatykovyMordulec::initRematchWithoutChange()
{
	this->scenesToExecute.clear();
	this->scenesToExecute.push_back(std::make_shared <GameEngine>(this->window));
	this->interSceneData[0] = this->interSceneData[1];
	this->interSceneData[1] = this->interSceneData[2];

}

