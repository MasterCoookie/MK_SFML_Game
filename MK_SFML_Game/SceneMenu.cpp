#include "SceneMenu.h"

SceneMenu::SceneMenu(sf::RenderWindow* win)
{
	this->window = win;
	this->setCharactersPicked(false);
	this->initBackground("menu.png");
}

void SceneMenu::run()
{
	while(!this->charactersPicked && this->window->isOpen()){ //UNCOMMENT TO WORK
		this->pollEvents();
		this->update();
		this->render();
	
	}
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
	sf::Event e;
	while (this->window->pollEvent(e)) {
		//red cross clicked
		if (e.Event::type == sf::Event::Closed) {
			this->window->close();
		}
		//were keys pressed?
		else if (e.Event::KeyPressed) {
			//escape button
			if (e.Event::key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			if (e.Event::key.code == sf::Keyboard::Space) {
				this->setCharactersPicked(true);
			}
		}
	}
}

void SceneMenu::update()
{
}

void SceneMenu::render()
{
	this->window->clear();
	this->window->draw(this->menuScreenSprite);
	this->window->display();
}

void SceneMenu::initBackground(std::string textureName)
{
	if (!this->menuScreenTexture.loadFromFile("./Textures/" + textureName)) {
		std::cout << " ! ERR: GAMEENGINE::INITWORLD: could not load menu img" << std::endl;
	}
	//set load to loaded texture
	this->menuScreenSprite.setTexture(this->menuScreenTexture);
}

void SceneMenu::setCharactersPicked(bool value)
{
	this->charactersPicked = value;
}
