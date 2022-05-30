#include "SelectableGUIElement.h"

SelectableGUIElement::SelectableGUIElement(std::string fileName, int left, int top, int width, int height)
{
	this->initTexture(*(this->texture), fileName);
	this->initSprite(left,top,width,height);
}

SelectableGUIElement::SelectableGUIElement(sf::Texture* tex, int left, int top, int width, int height, unsigned int xOnScreen, unsigned int yOnScreen)
{
	this->textureRect = new sf::IntRect(left, top, width, height);
	this->initSprite(*tex,this->textureRect); 
	this->setPosition(static_cast<float>(xOnScreen), static_cast<float>(yOnScreen)); 
}

SelectableGUIElement::~SelectableGUIElement()
{

}

void SelectableGUIElement::update()
{
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


