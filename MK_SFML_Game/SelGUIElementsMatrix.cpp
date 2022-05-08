#include "SelGUIElementsMatrix.h"

SelGUIElementsMatrix::SelGUIElementsMatrix(std::string texName, int nrows, int  ncols, int elementWidth, int elementHeight)
{
	this->initTexture(texName);
	this->initVariables(elementHeight, elementWidth);
	this->initCharactersMatrix(nrows, ncols);
}

SelGUIElementsMatrix::~SelGUIElementsMatrix()
{
	delete this->charactersTexture;
}

void SelGUIElementsMatrix::render(sf::RenderTarget* win)
{
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			charactersMatrix[i * this->cols + j]->render(win);
		}
	}
}

void SelGUIElementsMatrix::initTexture(std::string texName)
{
	this->charactersTexture = new sf::Texture;
	if (!this->charactersTexture->loadFromFile(texName)) {
		std::cout << " ! ERR: SelGUIElementsMatrix::constructor: could not load tex img" << std::endl;
	};
}

void SelGUIElementsMatrix::initVariables(int elementHeight, int elementWidth)
{
	this->elementHeight = elementHeight;
	this->elementWidth = elementWidth;
}

void SelGUIElementsMatrix::initCharactersMatrix(int nrows, int ncols)
{
	this->rows = nrows;
	this->cols = ncols;
	this->charactersMatrix.resize(this->rows * this->cols);
	int top, left;
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			charactersMatrix[i * (this->cols) + j] = new SelectableGUIElement(this->charactersTexture,left,top,this->elementWidth,this->elementHeight );
		}
	}
}
