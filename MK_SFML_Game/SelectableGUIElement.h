#pragma once
#include "GameObject.h"
class SimpleGUIElement :
    public GameObject
{
public:
    SimpleGUIElement();
    SimpleGUIElement(std::string fileName, int left, int top, int width, int height);
    SimpleGUIElement(std::shared_ptr<sf::Texture>, int left, int top, int width, int height,unsigned int xOnScreen, unsigned int yOnScreen);
    ~SimpleGUIElement();
    void update();
    void render(std::shared_ptr<sf::RenderTarget> win);
    void switchSprite(sf::Texture& tex,int left);
private:
    void initVariables() override;
};

