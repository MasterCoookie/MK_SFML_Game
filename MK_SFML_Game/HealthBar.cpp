#include "HealthBar.h"

HealthBar::HealthBar(bool isLeft)
{
	this->isLeft = isLeft;
	this->healthShape = new sf::RectangleShape;
	this->healthShape->setFillColor(sf::Color(255, 0, 0));
	this->healthShape->setSize({ 50.f,400.f });
	if (this->isLeft) {
		this->healthShape->setPosition({ 50,50 });
		this->originalPos = sf::Vector2f(50, 50);
	}
	else {
		this->healthShape->setPosition({ 1280 - 450,50 });
		this->originalPos = sf::Vector2f(1280 - 450, 50);
	}
}

void HealthBar::render(sf::RenderWindow* win)
{
	win->draw(*(this->healthShape));
}
