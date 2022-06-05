#pragma once
#include "GameGUIElement.h"
#include "BackgroundElement.h"
class Arena   
{
public:
    Arena();
    void render(std::shared_ptr<sf::RenderTarget> win);
    void reset();
private:
    std::vector<std::unique_ptr<BackgroundElement>> vectorOfElements;
};

