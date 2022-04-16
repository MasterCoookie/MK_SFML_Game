#pragma once
#include "Scene.h"
class SceneMenu :
    public Scene
{
public:
	SceneMenu(sf::RenderWindow* win);

	void run() override;

	std::vector<std::string> getResult() override;
	void setInterSceneValues(std::vector<std::string>& vec) override;
	void pollEvents() override;


	void update() override;



	void render() override;
private:
	sf::RenderWindow* window;
};

