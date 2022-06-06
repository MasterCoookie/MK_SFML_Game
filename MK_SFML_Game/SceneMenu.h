#pragma once
#include "Scene.h"
#include "SelGUIElementsMatrix.h"
#include "PickedCharacterDisplay.h"
class SceneMenu :
    public Scene
{
public:
	SceneMenu(std::shared_ptr<sf::RenderWindow> win);

	void run() override;

	std::vector<std::string> getResult() override;
	void setInterSceneValues(std::vector<std::string>& vec) override;
private:
	void pollEvents() override;
	void update() override;
	void render() override;
	void setAreCharactersPicked(bool val);
private:
	void initVariables();
	void initCharactersMatrix(std::string textureName);
	void initBackground(std::string textureName);
	void initText();
	std::unique_ptr<sf::Texture> menuScreenTexture;
	sf::Sprite menuScreenSprite;
	std::unique_ptr<SelGUIElementsMatrix> matrix;
	std::unique_ptr < PickedCharacterDisplay > playerOneDisplay;
	std::unique_ptr < PickedCharacterDisplay > playerTwoDisplay;
	std::shared_ptr<sf::Font> font;
	sf::Text PickYour;
	sf::Text player1;
	sf::Text player2;
	bool arePicked;
	int sincePlayerOneSwitched;
	int sincePlayerTwoSwitched;
	int switchingLimit;
	int playerOneChoice;
	int playerTwoChoice;
	

};

