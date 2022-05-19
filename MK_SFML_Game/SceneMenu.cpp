#include "SceneMenu.h"

SceneMenu::SceneMenu(sf::RenderWindow* win)
{
	this->window = win;
	this->initBackground("menu.png");
	this->initVariables();
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
			else if (e.Event::key.code == sf::Keyboard::Space) {			//Written to ommit the menu screen while developing the game
				this->arePicked = true;					//
			}
		}
	}
}
void SceneMenu::update()
{
	//test
	this->sincePlayerOneSwitched += 1;
	this->sincePlayerTwoSwitched += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		this->arePicked = true;
	}
	if (this->sincePlayerOneSwitched > this->switchingLimit) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->matrix->update(PlayerNumber::ONE, Direction::UP);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->matrix->update(PlayerNumber::ONE, Direction::DOWN);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->matrix->update(PlayerNumber::ONE, Direction::LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->matrix->update(PlayerNumber::ONE, Direction::RIGHT);
		}
		this->sincePlayerOneSwitched = 0;
	}
	if (this->sincePlayerTwoSwitched > this->switchingLimit) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			this->matrix->update(PlayerNumber::TWO, Direction::UP);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			this->matrix->update(PlayerNumber::TWO, Direction::DOWN);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			this->matrix->update(PlayerNumber::TWO, Direction::LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			this->matrix->update(PlayerNumber::TWO, Direction::RIGHT);
		}
		this->sincePlayerTwoSwitched = 0;
	}
	
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

void SceneMenu::initVariables()
{
	this->arePicked = false;
	this->switchingLimit = 5;
	this->sincePlayerOneSwitched = 0;
	this->sincePlayerTwoSwitched = 0;
}
