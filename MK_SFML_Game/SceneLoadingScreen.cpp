#include "SceneLoadingScreen.h"

SceneLoadingScreen::SceneLoadingScreen() {}
SceneLoadingScreen::SceneLoadingScreen(sf::RenderWindow* win)
{
	this->window = win;
}
;

SceneLoadingScreen::~SceneLoadingScreen() {};

void SceneLoadingScreen::run() {};

std::string SceneLoadingScreen::getResult() { return ""; };

void SceneLoadingScreen::pollEvents() {};

void SceneLoadingScreen::update() {};

void SceneLoadingScreen::render() {};

