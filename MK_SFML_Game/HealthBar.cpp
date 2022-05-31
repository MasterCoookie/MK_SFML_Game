#include "HealthBar.h"

HealthBar::HealthBar(bool isLeft)
{
	this->isLeft = isLeft;
	this->healthShape = new sf::RectangleShape;
	this->healthShape->setFillColor(sf::Color(255, 0, 0));
	this->healthShape->setSize({ 450.f, 50.f });
	if (this->isLeft) {
		this->healthShape->setPosition({ 730.f,50.f });
		this->originalPos = sf::Vector2f(50.f, 50.f);
	}
	else {
		this->healthShape->setPosition({ 1380.f,50.f });
		this->originalPos = sf::Vector2f(1280 - 450, 50);
	}
}

void HealthBar::render(sf::RenderWindow* win)
{
	win->draw(*(this->healthShape));
}

void HealthBar::update(float currentHealth)
{
	if (this->isLeft) {
		this->healthShape->setSize({ 450.f * currentHealth / 100,50.f });
	}
}
