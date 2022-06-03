#include "SelectableGUIElement.h"

SimpleGUIElement::SimpleGUIElement()
{
}

SimpleGUIElement::SimpleGUIElement(std::string fileName, int left, int top, int width, int height)
{
	this->initTexture(*(this->texture), fileName);
	this->initSprite(left,top,width,height);
}

SimpleGUIElement::SimpleGUIElement(std::shared_ptr<sf::Texture> tex, int left, int top, int width, int height, unsigned int xOnScreen, unsigned int yOnScreen)
{
	this->textureRect = std::make_shared<sf::IntRect>(left, top, width, height);
	this->initSprite(*tex,this->textureRect); 
	this->setPosition(static_cast<float>(xOnScreen), static_cast<float>(yOnScreen)); 
}

SimpleGUIElement::~SimpleGUIElement()
{

}

void SimpleGUIElement::update()
{
}

void SimpleGUIElement::render(std::shared_ptr<sf::RenderTarget> win)
{
	win->draw(sprite);
}

void SimpleGUIElement::switchSprite(sf::Texture& tex, int left)
{
	sf::IntRect recOfNew = this->getIntRect();
	recOfNew.left = left;
	this->setIntRect(tex, recOfNew);
}

void SimpleGUIElement::initVariables()
{
}


