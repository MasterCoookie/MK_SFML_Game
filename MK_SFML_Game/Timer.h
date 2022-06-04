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
	void render(std::shared_ptr<sf::RenderTarget> win)override;
	void move(float offsetX, float offsetY) override;
	void reset() override;
private:
	void initText();
	std::unique_ptr<sf::Font> font;
	sf::Text text;
};

