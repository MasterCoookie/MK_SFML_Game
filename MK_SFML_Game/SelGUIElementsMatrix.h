#pragma once
#include "SelectableGUIElement.h"
class SelGUIElementsMatrix
{
public:
	SelGUIElementsMatrix(std::string texName, int nrows, int  ncols, int elementWidth,int elementHeight);
	~SelGUIElementsMatrix();
	void render(sf::RenderTarget* win);
	int getPlayerOneChoice();
	int getPlayerTwoChoice();

private:	
	int rows, cols;
	int elementWidth, elementHeight;
	sf::Texture* charactersTexture;
	std::vector<SelectableGUIElement*> charactersMatrix;
	int playerOneChoice;
	int playerTwoChoice;
private:
	void initTexture(std::string texName);
	void initVariables(int elementHeight, int elementWidth);
	void initCharactersMatrix(int nrows, int ncols, int offsetScreen, int offsetTexture);

};

