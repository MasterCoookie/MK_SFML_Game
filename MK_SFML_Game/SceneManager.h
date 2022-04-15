#pragma once
#include "GameEngine.h"
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

