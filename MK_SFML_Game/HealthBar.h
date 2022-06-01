
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class HealthBar
{
public:
	HealthBar(bool isLeft);
	void render(sf::RenderWindow* win);
	void update(float currentHealth);
	void move(float offsetX, float offsetY);
private:
	bool isLeft;
	sf::RectangleShape* healthShape;
	sf::RectangleShape* backgroundShape;
	sf::Vector2f originalPos;
};

