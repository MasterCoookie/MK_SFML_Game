#pragma once
#include "GameGUIElement.h"
class GUIMessage :
    public GameGUIElement
{
public:
    GUIMessage();
    void move(float offsetX, float offsetY);
    void render(sf::RenderWindow* win);
    void updateMessage(std::string msg);
private:
    std::unique_ptr<sf::Font> font;
    sf::Text text;
};

