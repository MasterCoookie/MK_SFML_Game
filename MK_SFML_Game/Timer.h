#pragma once
#include <iostream>
#include <iomanip>
#include <sstream> 
#include "GameGUIElement.h"
class Timer : public GameGUIElement	
{
public:
	Timer();
	void update(sf::Time time) ;
	void render(sf::RenderWindow* win)override;
	void move(float offsetX, float offsetY) override;
private:
	void initText();
	sf::Font* font;
	sf::Text text;
};

