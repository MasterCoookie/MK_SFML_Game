#include "SelGUIElementsMatrix.h"

SelGUIElementsMatrix::SelGUIElementsMatrix(std::string texName, int nrows, int  ncols, int elementWidth, int elementHeight)
{
	this->initTexture(texName);
	this->initVariables(elementHeight, elementWidth);
	this->initCharactersMatrix(nrows, ncols,230,200); //  @TODO argumenty maj¹ byæ z konstruktora
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

void SelGUIElementsMatrix::initCharactersMatrix(int nrows, int ncols, int offsetScreen,int offsetTexture)
{
	this->rows = nrows;
	this->cols = ncols;
	this->charactersMatrix.resize(this->rows * this->cols);
	sf::Vector2u vecOnScreen(250 + 60, 150);
	int positionOnTexture = 0;
	int offsetOnScreen = offsetScreen, offsetOnTexture=offsetTexture;
	int top=0, left=0; //to tak nie moze zostac 
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) { //TODO
			charactersMatrix[i * (this->cols) + j] = new SelectableGUIElement(this->charactersTexture, 0, positionOnTexture, this->elementWidth,this->elementHeight, vecOnScreen.x, vecOnScreen.y ); //przepisac konstruktor
			vecOnScreen.x += offsetOnScreen;
			positionOnTexture += offsetOnTexture;
		}
		vecOnScreen.y += offsetOnScreen;
		vecOnScreen.x -= this->cols * offsetOnScreen;
		}
}
