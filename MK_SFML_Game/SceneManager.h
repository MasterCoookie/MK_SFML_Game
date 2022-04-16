#pragma once

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

	void initWindow();
	
};

