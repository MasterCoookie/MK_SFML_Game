#include "SelectableGUIElement.h"

SelectableGUIElement::SelectableGUIElement(std::string fileName, int left, int top, int width, int height)
{
	this->initTexture(*(this->texture), fileName);
	this->isSelected = false;
	this->initSprite(left,top,width,height);
}

SelectableGUIElement::SelectableGUIElement(sf::Texture* tex, int left, int top, int width, int height, unsigned int xOnScreen, unsigned int yOnScreen)
{
	this->textureRect = new sf::IntRect(left, top, width, height);
	this->isSelected = false;
	this->initSprite(*tex,this->textureRect); //mo�e si� dupi�
	this->setPosition(static_cast<float>(xOnScreen), static_cast<float>(yOnScreen)); //to do konwersja
}

SelectableGUIElement::~SelectableGUIElement()
{

}

void SelectableGUIElement::update()
{
	if (this->isSelected) {

	}
	else {

	}
}

void SelectableGUIElement::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

void SelectableGUIElement::switchSprite(sf::Texture& tex, int left)
{
	sf::IntRect recOfNew = this->getIntRect();
	recOfNew.left = left;
	this->setIntRect(tex, recOfNew);
}


void SelectableGUIElement::initVariables()
{

}

void SelectableGUIElement::switchState()
{
	this->isSelected = this->isSelected ? false : true;
	this->update();
}
