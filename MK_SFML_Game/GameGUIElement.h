#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class GameGUIElement
{
public:
	virtual void render(std::shared_ptr<sf::RenderTarget> win) = 0;
	virtual void move(float offsetX, float offsetY) = 0;
	virtual void reset()=0;
};

