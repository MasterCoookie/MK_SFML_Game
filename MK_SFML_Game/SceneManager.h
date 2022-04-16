#pragma once

#include "GameEngine.h"
#include "SceneLoadingScreen.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void run();
private:

	sf::RenderWindow* window;

	void initWindow();
	
};

