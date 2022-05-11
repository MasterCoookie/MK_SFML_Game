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
	this->initSprite(*tex,this->textureRect); //mo¿e siê dupiæ
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

void SelectableGUIElement::switchSprite(int newLeft)
{
	int top, height, width;
	top = this->textureRect->top;
	height = this->textureRect->height;
	width = this->textureRect->width;
	delete this->textureRect;
	this->textureRect = new sf::IntRect(newLeft, top, width, height);
	this->sprite.setTextureRect((*this->textureRect));
}

void SelectableGUIElement::initVariables()
{
}

void SelectableGUIElement::switchState()
{
	this->isSelected = this->isSelected ? false : true;
	this->update();
}
