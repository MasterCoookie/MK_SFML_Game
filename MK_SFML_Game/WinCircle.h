#pragma once
#include "GameGUIElement.h"
class WinCircle :
    public GameGUIElement
{
public:
    WinCircle(bool isLeft);
    void update();
    void render(std::shared_ptr<sf::RenderTarget> win) override;
    void move(float offsetX, float offsetY) override;
    void reset() override;
private:
    std::unique_ptr<sf::CircleShape> circle;
    bool isVisble;
    bool isLeft;
};

