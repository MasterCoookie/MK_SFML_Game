#pragma once
#include "SelectableGUIElement.h"
#include "Animator.h"
class PickedCharacterDisplay :
    public SimpleGUIElement
{
    PickedCharacterDisplay(int width, int height, bool isLeft);
    void switchSprite(sf::Texture& tex, int top);
private:
    Animator* animator;
};

