#pragma once
#include "GameEngine.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void run();
private:

	sf::Window* window;

	void initWindow();
	void deleteWindow();
};

