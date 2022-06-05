#pragma once
#include "GameGUIElement.h"
class BackgroundElement :
    public GameGUIElement
{
public:
    BackgroundElement(std::shared_ptr<sf::Texture> tex, int postionX, int positionY);
    void render(std::shared_ptr<sf::RenderTarget> win);
    void move(float offsetX, float offsetY);
    void reset();
private:
    std::shared_ptr<sf::Texture> texture;
   
    sf::Sprite sprite;
    sf::Vector2f originalPosition;

};

