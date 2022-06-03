#pragma once
#include "SelectableGUIElement.h"
#include "Animator.h"
class PickedCharacterDisplay :
    public SimpleGUIElement
{
public:
    PickedCharacterDisplay(int width, int height, bool isLeft);
    void update(int i=-1);
private:
    std::unique_ptr<Animator> animator;
};

