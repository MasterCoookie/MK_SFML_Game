#pragma once
#include "Scene.h"
class SceneLoadingScreen :
    public Scene
{
public:
    SceneLoadingScreen();
    ~SceneLoadingScreen();

    void run() override;
    std::string getResult() override;
    
    void pollEvents() override;
    void update() override;
    void render() override;
private:


};

