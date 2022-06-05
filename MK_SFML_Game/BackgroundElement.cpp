#include "BackgroundElement.h"

BackgroundElement::BackgroundElement(std::shared_ptr<sf::Texture> tex, int postionX, int positionY)
{
	this->texture = tex;
	this->sprite.setTexture(*(this->texture));
	this->sprite.setPosition(postionX, positionY);
	this->originalPosition = { (float)postionX, (float)positionY };
}

void BackgroundElement::render(std::shared_ptr<sf::RenderTarget> win)
{
	win->draw(this->sprite);
}

void BackgroundElement::move(float offsetX, float offsetY)
{
	this->sprite.move(offsetX, offsetY);
}

void BackgroundElement::reset()
{
	this->sprite.setPosition(this->originalPosition);
}
