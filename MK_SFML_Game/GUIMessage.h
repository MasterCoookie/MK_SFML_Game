#pragma once
#include <sstream>
#include <iomanip>
#include "GameGUIElement.h"
class GUIMessage :
    public GameGUIElement
{
public:
    GUIMessage();
    void move(float offsetX, float offsetY);
    void render(std::shared_ptr<sf::RenderTarget> win);
    void reset()override;
    void updateMessage(std::string msg, std::shared_ptr<sf::View> view);
    std::string transform(int n,std::string s);
private:
    std::unique_ptr<sf::Font> font;
    sf::Text text;
};

