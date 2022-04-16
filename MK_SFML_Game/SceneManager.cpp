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
	GameEngine game(this->window, "char1", "char2");
	SceneLoadingScreen loading(this->window);
	Scene* ptr1 = &loading;
	Scene* ptr2 = &game;


	std::vector<Scene*> vec;
	vec.push_back(ptr1);
	vec.push_back(ptr2);
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

