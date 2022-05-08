#include "SceneMenu.h"

SceneMenu::SceneMenu(sf::RenderWindow* win)
{
	this->window = win;
	this->setCharactersPicked(false);
	this->initBackground("menu.png");
	this->initCharactersMatrix("characters.png");
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
	std::vector<std::string> vec = { "char1", "char2" }; //returns PATH to the files with chosen characters
	return vec;

}

void SceneMenu::setInterSceneValues(std::vector<std::string>& vec)
{
	//does nothing, no need to
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
			if (e.Event::key.code == sf::Keyboard::Space) {			//Written to ommit the menu screen while developing the game
				this->setCharactersPicked(true);					//
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

void SceneMenu::initCharactersMatrix(std::string textureName)
{
	const int sizeOfMatrix = 3;
	this->charactersTexture = new sf::Texture;
	if (!this->charactersTexture->loadFromFile("./Textures/" + textureName)) {
		std::cout << " ! ERR: GAMEENGINE::INITWORLD: could not load menu img" << std::endl;
	}
	for (int i = 0; i < sizeOfMatrix * sizeOfMatrix; i++) {

	}
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
