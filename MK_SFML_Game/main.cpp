#include <iostream>

#include "SceneManager.h"
#include "LoadingScreen.h"
#include "AttackMovesMatrix.h"
int main() {

	//SceneManager kumbat;
	//kumbat.run();
	sf::RenderWindow* win = new sf::RenderWindow(sf::VideoMode(1280, 960), "Patykovy Mordulec", sf::Style::Titlebar | sf::Style::Close);
	win->setFramerateLimit(30);
	LoadingScreen load(win, "char1", "char2");
	load.loadPlayers();
}