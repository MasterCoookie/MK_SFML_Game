#include "SceneMenu.h"

SceneMenu::SceneMenu(sf::RenderWindow* win)
{
	this->window = win;
	this->arePicked=false;
	this->initBackground("menu.png");
	this->initCharactersMatrix("./SceneMenu/elem1.png");
	
}

void SceneMenu::run()
{
	while(!this->arePicked && this->window->isOpen()){ //UNCOMMENT TO WORK
		this->pollEvents();
		this->update();
		this->render();
	
	}
}

std::vector<std::string> SceneMenu::getResult()
{
	//std::vector<std::string> vec = { "char" + std::to_string(this->matrix->getPlayerOneChoice()+1), "char" + std::to_string(this->matrix->getPlayerTwoChoice() + 1) }; //returns PATH to the files with chosen characters
	
	std::vector<std::string> vec = { "char1","char2" };
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
				this->arePicked = true;					//
			}
		}
	}
}

void SceneMenu::update()
{
	//test
	//this->matrix->update(PlayerNumber::ONE, Direction::UP); // @ TODO IMPLEMENT
}

void SceneMenu::render()
{
	this->window->clear();
	this->window->draw(this->menuScreenSprite);
	this->matrix->render(this->window);
	this->window->display();
}

void SceneMenu::initCharactersMatrix(std::string textureName)
{
	this->matrix = new SelGUIElementsMatrix(textureName, 3, 3, 200, 200);
}

void SceneMenu::initBackground(std::string textureName)
{
	if (!this->menuScreenTexture.loadFromFile("./Textures/" + textureName)) {
		std::cout << " ! ERR: GAMEENGINE::INITWORLD: could not load menu img" << std::endl;
	}
	//set load to loaded texture
	this->menuScreenSprite.setTexture(this->menuScreenTexture);
}

void SceneMenu::setAreCharactersPicked(bool value)
{
	this->arePicked = value;
}
