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
    void switchSprite(int left);
private:
    void initVariables();
    bool isSelected; //TODO zmieniæ na enum - trzy stany, selected by player1, player2, nonselected
private:
    void switchState();
};

