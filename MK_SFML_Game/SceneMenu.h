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
private:
	void pollEvents() override;
	void update() override;
	void render() override;
	void initBackground(std::string textureName);
	void setCharactersPicked(bool value);
private:
	sf::RenderWindow* window;
	sf::Texture menuScreenTexture;
	sf::Sprite menuScreenSprite;
	bool charactersPicked;
};

