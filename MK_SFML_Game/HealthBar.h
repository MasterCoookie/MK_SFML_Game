
#pragma once
#include <iostream>
#include "GameGUIElement.h"
class HealthBar : public GameGUIElement
{
public:
	HealthBar(bool isLeft, std::string name);
	void render(std::shared_ptr<sf::RenderTarget> win) override;
	void update(float currentHealth);
	void move(float offsetX, float offsetY) override;
	void reset() override;
private:
	void initText(std::string name);
	void initShapes();
	void setPosition(float x, float y);
	bool isLeft;
	std::unique_ptr < sf::RectangleShape> healthShape;
	std::unique_ptr < sf::RectangleShape> backgroundShape;
	sf::Vector2f originalPos;
	std::unique_ptr<sf::Font> font;
	sf::Text text;
};

