
#pragma once
#include "GameGUIElement.h"
class HealthBar : public GameGUIElement
{
public:
	HealthBar(bool isLeft);
	void render(sf::RenderWindow* win) override;
	void update(float currentHealth);
	void move(float offsetX, float offsetY) override;
private:
	bool isLeft;
	sf::RectangleShape* healthShape;
	sf::RectangleShape* backgroundShape;
	sf::Vector2f originalPos;
};

