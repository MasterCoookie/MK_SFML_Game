#include "HealthBar.h"

HealthBar::HealthBar(bool isLeft)
{
	this->isLeft = isLeft;
	this->healthShape = new sf::RectangleShape;
	this->healthShape->setFillColor(sf::Color(255, 0, 0));
	this->healthShape->setSize({ 450.f, 50.f });
	if (this->isLeft) {
		this->healthShape->setPosition({ 730.f,50.f });
		this->originalPos = sf::Vector2f(730.f, 50.f);
	}
	else {
		this->healthShape->setPosition({ 1380.f,50.f });
		this->originalPos = sf::Vector2f(1380.f, 50.f);
	}
}

void HealthBar::render(sf::RenderWindow* win)
{
	win->draw(*(this->healthShape));
}

void HealthBar::update(float currentHealth)
{
	this->healthShape->setSize({ 450.f * currentHealth / 100,50.f });
	if (this->isLeft) {}
	else {
		sf::Vector2f newVec = this->originalPos;
		newVec.x += 450.f-450.f * currentHealth / 100.f;
		this->healthShape->setPosition(newVec);
	}
}

void HealthBar::move(float offsetX, float offsetY)
{
	this->healthShape->move(offsetX, offsetY);
	this->originalPos.x += offsetX;
	this->originalPos.y += offsetY;
}
