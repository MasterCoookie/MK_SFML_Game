#include "SceneManager.h"
SceneManager::SceneManager()
{
	this->initWindow();
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::run()
{
	GameEngine game(this->window);
	SceneLoadingScreen loading(this->window);
	std::vector<Scene*> vec;
	vec.push_back(&loading);
	vec.push_back(&game);
	std::vector<std::string> vec2 = { "char1","char2" };
	game.setInterSceneValues(vec2);
	for (auto it = vec.begin(); it != vec.end(); it++) {
		(*it)->run();
	}
	

}

void SceneManager::initWindow()
{
	//initializes window with set params
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 960), "Mortul Kombet", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

