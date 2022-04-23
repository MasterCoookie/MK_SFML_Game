#include "SceneManager.h"
SceneManager::SceneManager()
{
	this->initWindow();
	this->interSceneData = { "" };
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::run()
{
	
	//std::vector<std::string> vec2={""};
	//while (vec2[0] == "") {
		GameEngine game(this->window);
		SceneLoadingScreen loading(this->window);
		SceneMenu menu(this->window);
		std::vector<Scene*> vec;
		vec.push_back(&loading);
		vec.push_back(&menu);
		vec.push_back(&game);
		std::for_each(vec.begin(), vec.end(), [this](Scene* s) {	// for each <3 brachu 
																	// for each <3 brachu 
			this->executeScene(s);									// for each <3 brachu 
																	// for each <3 brachu 
			});
		//for (auto it = vec.begin(); it != vec.end(); it++) {
		//	(*it)->setInterSceneValues(vec2);
		//	(*it)->run();
		//	vec2 = (*it)->getResult();
		//}
	//}
	

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
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 960), "Mortul Kombet", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

