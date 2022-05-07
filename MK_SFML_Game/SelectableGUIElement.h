#pragma once
#include "GameObject.h"
class SelectableGUIElement :
    public GameObject
{
public:
    SelectableGUIElement(std::string fileName, int left, int top, int width, int height);
    ~SelectableGUIElement();
    void update();
    void render(sf::RenderTarget* target);
private:
    void initVariables();
    bool isSelected;
private:
    void switchState();
};

