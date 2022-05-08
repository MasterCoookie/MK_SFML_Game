#include "SelectableGUIElement.h"

SelectableGUIElement::SelectableGUIElement(std::string fileName, int left, int top, int width, int height)
{
	this->initTexture(*(this->texture), fileName);
	this->isSelected = false;
	this->initSprite(left,top,width,height);
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

void SelectableGUIElement::initVariables()
{
}

void SelectableGUIElement::switchState()
{
	this->isSelected = this->isSelected ? false : true;
	this->update();
}
