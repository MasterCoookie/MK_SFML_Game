#include "SceneMenu.h"

SceneMenu::SceneMenu(sf::RenderWindow* win)
{
	this->window = win;
}

void SceneMenu::run()
{
}

std::vector<std::string> SceneMenu::getResult()
{
	std::vector<std::string> vec = { "char1", "char2" };
	return vec;

}

void SceneMenu::setInterSceneValues(std::vector<std::string>& vec)
{
}

void SceneMenu::pollEvents()
{
}

void SceneMenu::update()
{
}

void SceneMenu::render()
{
}
