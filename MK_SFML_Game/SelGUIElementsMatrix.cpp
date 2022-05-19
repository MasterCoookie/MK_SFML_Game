#include "SelGUIElementsMatrix.h"

SelGUIElementsMatrix::SelGUIElementsMatrix(std::string texName, int nrows, int  ncols, int elementWidth, int elementHeight)
{
	this->initTexture(texName);
	this->initVariables(elementHeight, elementWidth);
	this->initCharactersMatrix(nrows, ncols, 230, 200); //  @TODO argumenty maj¹ byæ z konstruktora
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
	if (player == PlayerNumber::ONE) {
		currChoice = this->playerOneChoice;
		otherCurrChoice = this->playerTwoChoice;
	}
	else {
		currChoice = this->playerTwoChoice;
		otherCurrChoice = this->playerOneChoice;
	}
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
	currChoice += offset;
	if (currChoice >=0 && currChoice < this->charactersMatrix.size()) {
		
		sf::IntRect recOfOld = this->charactersMatrix[currChoice - offset]->getIntRect();
		recOfOld.left = 0;
		this->charactersMatrix[currChoice - offset]->setIntRect(*(this->charactersTexture),recOfOld);
		if (currChoice == otherCurrChoice) {
			//set to both selected
			sf::IntRect recOfNew = this->charactersMatrix[currChoice]->getIntRect();
			recOfNew.left = 600;
			this->charactersMatrix[currChoice]->setIntRect(*(this->charactersTexture), recOfNew);
			this->playerOneChoice = currChoice;
			this->playerTwoChoice = currChoice;
		}
		else if (player == PlayerNumber::ONE) {
			
			//set first player
			sf::IntRect recOfNew = this->charactersMatrix[currChoice]->getIntRect();
			recOfNew.left = 200;
			this->charactersMatrix[currChoice]->setIntRect(*(this->charactersTexture), recOfNew);
			this->playerOneChoice = currChoice;
			//set second player
			sf::IntRect recOfDifferent = this->charactersMatrix[this->playerTwoChoice]->getIntRect();
			recOfDifferent.left = 400;
			this->charactersMatrix[this->playerTwoChoice]->setIntRect(*(this->charactersTexture),recOfDifferent);
		}
		else if (player == PlayerNumber::TWO) {
			//set second player
			sf::IntRect recOfNew = this->charactersMatrix[currChoice]->getIntRect();
			recOfNew.left = 400;
			this->charactersMatrix[currChoice]->setIntRect(*(this->charactersTexture), recOfNew);
			this->playerTwoChoice = currChoice;
			//set first player
			sf::IntRect recOfDifferent = this->charactersMatrix[this->playerOneChoice]->getIntRect();
			recOfDifferent.left = 200;
			this->charactersMatrix[this->playerOneChoice]->setIntRect(*(this->charactersTexture), recOfDifferent);
		
		}
	}
	else {
		//do nothing
		
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
