#pragma once
#include "Scene.h"

class SceneLoadingScreen :
    public Scene
{
public:
    SceneLoadingScreen();
    SceneLoadingScreen(sf::RenderWindow* win);
    ~SceneLoadingScreen();

    void run() override;
    std::vector<std::string> getResult() override;
    void setInterSceneValues(std::vector<std::string>& vec) override;
    void pollEvents() override;
    void update() override;
    void render() override;
private:
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

