#pragma once
#include <memory>
#include "SelectableGUIElement.h"

enum class PlayerNumber {ONE,TWO};
enum class Direction {UP,DOWN,LEFT,RIGHT};
class SelGUIElementsMatrix
{
public:
	SelGUIElementsMatrix(std::string texName, int nrows, int  ncols, int elementWidth,int elementHeight);
	~SelGUIElementsMatrix();
	void render(sf::RenderTarget* win);
	int getPlayerOneChoice();
	int getPlayerTwoChoice();
	void update(PlayerNumber player, Direction dir);
private:	
	int rows, cols;
	int elementWidth, elementHeight;
	sf::Texture* charactersTexture;
	std::vector<std::unique_ptr<SimpleGUIElement>> charactersMatrix;
	int playerOneChoice;
	int playerTwoChoice;
private:
	void initTexture(std::string texName);
	void initVariables(int elementHeight, int elementWidth);
	void initCharactersMatrix(int nrows, int ncols, int offsetScreen, int offsetTexture);

};

