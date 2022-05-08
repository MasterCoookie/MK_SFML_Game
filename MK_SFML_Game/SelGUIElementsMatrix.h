#pragma once
#include "SelectableGUIElement.h"
class SelGUIElementsMatrix
{
public:
	SelGUIElementsMatrix(std::string texName, int nrows, int  ncols, int elementWidth,int elementHeight);
	~SelGUIElementsMatrix();
	void render(sf::RenderTarget* win);
private:	
	int rows, cols;
	int elementWidth, elementHeight;
	sf::Texture* charactersTexture;
	std::vector<SelectableGUIElement*> charactersMatrix;
private:
	void initTexture(std::string texName);
	void initVariables(int elementHeight, int elementWidth);
	void initCharactersMatrix(int nrows, int ncols);
};

