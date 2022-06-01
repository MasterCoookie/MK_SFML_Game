#include "WinCircle.h"

WinCircle::WinCircle(bool isLeft)
{
	this->isLeft = isLeft;
	this->circle = new sf::CircleShape;
	this->circle->setRadius(20.f);
	this->circle->setFillColor(sf::Color(255, 255, 0));
	this->isVisble = false;
	if (isLeft) {
		this->circle->setPosition({ 660, 200 });
	}
	else {
		this->circle->setPosition({ 1280 * 2 - 700, 200 });
	}
}

void WinCircle::update()
{
	this->isVisble = true;
}

void WinCircle::render(sf::RenderWindow* win)
{
	if (isVisble) {
		win->draw(*(this->circle));
	}
	else {
		//do not display
	}
}

void WinCircle::move(float offsetX, float offsetY)
{
	this->circle->move(offsetX, offsetY);
}
