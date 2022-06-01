#pragma once
#include "GameObject.h"
class SimpleGUIElement :
    public GameObject
{
public:
    SimpleGUIElement();
    SimpleGUIElement(std::string fileName, int left, int top, int width, int height);
    SimpleGUIElement(sf::Texture*, int left, int top, int width, int height,unsigned int xOnScreen, unsigned int yOnScreen);
    ~SimpleGUIElement();
    void update();
    void render(sf::RenderTarget* target);
    void switchSprite(sf::Texture& tex,int left);
private:
    void initVariables() override;
};

