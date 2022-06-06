#pragma once
#include <algorithm>
#include "LoadingScreen.h"
#include "GameEngine.h"
#include "SceneWelcomeScreen.h"
#include "SceneMenu.h"

class GamePatykovyMordulec
{
public:
	GamePatykovyMordulec();
	~GamePatykovyMordulec();
	void run();
private:

	std::shared_ptr<sf::RenderWindow> window;
	void executeScene(std::shared_ptr<Scene> s);
	void initWindow();
	void initScenesToExecute();
	void initRematch();
	void initRematchWithoutChange();
private:
	std::vector<std::string> interSceneData;
	std::vector<std::vector<std::string>> historyOfSceneData;
	std::vector<std::shared_ptr<Scene>> scenesToExecute;
};

