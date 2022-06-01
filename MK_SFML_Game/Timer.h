#pragma once
#include <iostream>
#include <iomanip>
#include <sstream> 
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Timer
{
public:
	Timer();
	void update(sf::Time time);
	void render(sf::RenderWindow* win);
	void move(float offsetX, float offsetY);
private:
	void initText();
	sf::Font* font;
	sf::Text text;
};

