#include "SceneLoadingScreen.h"

SceneLoadingScreen::SceneLoadingScreen() {}
SceneLoadingScreen::SceneLoadingScreen(sf::RenderWindow* win)
{
	this->window = win;
}
;

SceneLoadingScreen::~SceneLoadingScreen() {};

void SceneLoadingScreen::run() {};

std::vector<std::string> SceneLoadingScreen::getResult() {
	std::vector<std::string> vec;
	return vec; 
}
void SceneLoadingScreen::setInterSceneValues(std::vector<std::string>& vec)
{
};

void SceneLoadingScreen::pollEvents() {};

void SceneLoadingScreen::update() {};

void SceneLoadingScreen::render() {};

