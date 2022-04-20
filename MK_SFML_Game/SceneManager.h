#pragma once
#include <algorithm>
#include "GameEngine.h"
#include "SceneLoadingScreen.h"
#include "SceneMenu.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void run();
private:

	sf::RenderWindow* window;
	void executeScene(Scene* s);
	void initWindow();
private:
	std::vector<std::string> interSceneData;
};

