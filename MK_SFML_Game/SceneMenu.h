#pragma once
#include "Scene.h"
#include "SelGUIElementsMatrix.h"
#include "PickedCharacterDisplay.h"
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
	void initCharactersMatrix(std::string textureName);
	void initBackground(std::string textureName);
	void setAreCharactersPicked(bool val);
	void initVariables();
private:
	sf::RenderWindow* window;
	sf::Texture menuScreenTexture;
	sf::Sprite menuScreenSprite;
	SelGUIElementsMatrix* matrix;
	PickedCharacterDisplay* playerOneDisplay;
	PickedCharacterDisplay* playerTwoDisplay;
	bool arePicked;
	int sincePlayerOneSwitched;
	int sincePlayerTwoSwitched;
	int switchingLimit;
	int playerOneChoice;
	int playerTwoChoice;
	

};

