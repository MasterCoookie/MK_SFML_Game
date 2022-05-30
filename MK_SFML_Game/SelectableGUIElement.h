#pragma once
#include "GUIElement.h"
class SelectableGUIElement :
    public GUIElement
{
public:
    SelectableGUIElement(std::string fileName, int left, int top, int width, int height);
    SelectableGUIElement(sf::Texture*, int left, int top, int width, int height,unsigned int xOnScreen, unsigned int yOnScreen);
    ~SelectableGUIElement();
    void update();
    void render(sf::RenderTarget* target);
    void switchSprite(sf::Texture& tex,int left);
private:
    void initVariables() override;
};

