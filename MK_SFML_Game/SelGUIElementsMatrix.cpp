#include "SelGUIElementsMatrix.h"

SelGUIElementsMatrix::SelGUIElementsMatrix(std::string texName, int nrows, int  ncols, int elementWidth, int elementHeight)
{
	this->initTexture(texName);
	this->initVariables(elementHeight, elementWidth);
	this->initCharactersMatrix(nrows, ncols,230,200); //  @TODO argumenty maj¹ byæ z konstruktora
	this->playerOneChoice = 0;
	this->playerTwoChoice = this->cols - 1;
}

SelGUIElementsMatrix::~SelGUIElementsMatrix()
{
	delete this->charactersTexture;
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			delete this->charactersMatrix[i * this->cols + j];
		}
	}
}

void SelGUIElementsMatrix::render(sf::RenderTarget* win)
{
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			charactersMatrix[i * this->cols + j]->render(win);
		}
	}
}

int SelGUIElementsMatrix::getPlayerOneChoice()
{
	return this->playerOneChoice;
}

int SelGUIElementsMatrix::getPlayerTwoChoice()
{
	return this->playerTwoChoice;
}

void SelGUIElementsMatrix::update(PlayerNumber player, Direction dir)
{
	int currChoice, otherCurrChoice, offset;
	currChoice = player == PlayerNumber::ONE ? this -> playerOneChoice : this->playerTwoChoice;
	otherCurrChoice = player == PlayerNumber::TWO ? this -> playerOneChoice : this->playerTwoChoice;
	if (dir == Direction::UP) {
		offset = -3;
	}
	else if (dir == Direction::DOWN) {
		offset = 3;
	}
	else if (dir == Direction::LEFT) {
		offset = -1;
	}
	else if (dir == Direction::RIGHT) {
		offset = 1;
	}
	if ((currChoice + offset >= 0) && (currChoice + offset < this->charactersMatrix.size()) && (currChoice % (this->cols) + offset < this->cols)
		&& (currChoice%(this->cols) + offset >=0 )) {
		std::cout << "dupa\n";
		if (player == PlayerNumber::ONE) {
			this->playerOneChoice += offset;
		}
		else {
			this->playerTwoChoice += offset;
		}
	}
	else {
		//do nothing
		std::cout << "niedupa\n";
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
