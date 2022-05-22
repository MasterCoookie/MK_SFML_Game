#pragma once
#include "Scene.h"

class SceneWelcomeScreen :
    public Scene
{
public:
    SceneWelcomeScreen();
    SceneWelcomeScreen(sf::RenderWindow* win);
    ~SceneWelcomeScreen();

    void run() override;
    std::vector<std::string> getResult() override;
    void setInterSceneValues(std::vector<std::string>& vec) override;
    
private:
    void pollEvents() override;
    void update() override;
    void render() override;
    void initTexture(std::string name);
    void setCurrentSeconds(float num);
    void setShowForSeconds(float num);
    void setOverTime(bool value);
private:
    sf::RenderWindow* window;
    sf::Texture loadingScreenTexture;  
    sf::Sprite loadingScreenSprite;
    float showForSeconds;
    float currentSeconds;
    bool overTime;
};

