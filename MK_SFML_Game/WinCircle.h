#pragma once
#include "GameGUIElement.h"
class WinCircle :
    public GameGUIElement
{
public:
    WinCircle(bool isLeft);
    void update();
    void render(sf::RenderWindow* win) override;
    void move(float offsetX, float offsetY) override;
private:
    std::unique_ptr<sf::CircleShape> circle;
    bool isVisble;
    bool isLeft;
};

