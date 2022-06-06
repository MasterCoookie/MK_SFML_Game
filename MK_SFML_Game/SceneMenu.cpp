#include "SceneMenu.h"

SceneMenu::SceneMenu(std::shared_ptr<sf::RenderWindow> win)
{
	this->window = win;
	this->initBackground("menu.png");
	this->initVariables();
	this->initCharactersMatrix("./SceneMenu/elem1.png");
	this->initText();
	this->playerOneChoice = this->matrix->getPlayerOneChoice();
	this->playerTwoChoice = this->matrix->getPlayerTwoChoice();
	this->playerOneDisplay = std::make_unique<PickedCharacterDisplay>(150, 375, true);
	this->playerTwoDisplay = std::make_unique<PickedCharacterDisplay>(150, 375, false);
	this->playerOneDisplay->update(this->playerOneChoice);
	this->playerTwoDisplay->update(this->playerTwoChoice);

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
	std::string player1 = "char"+std::to_string(this->matrix->getPlayerOneChoice() + 1);
	std::string player2 = "char"+std::to_string(this->matrix->getPlayerTwoChoice()+1);
	std::cout << "Player One choice: " << player1 << std::endl;
	std::cout << "Player Two choice: " << player2 << std::endl;

	// DEBUG VERSION:
	std::vector<std::string> vec = { player1, player2 };
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
	if (this->playerOneChoice == this->matrix->getPlayerOneChoice()) {
		this->playerOneDisplay->update();
	}
	else {
		this->playerOneChoice = this->matrix->getPlayerOneChoice();
		this->playerOneDisplay->update(this->playerOneChoice);
	}
	if (this->playerTwoChoice == this->matrix->getPlayerTwoChoice()) {
		this->playerTwoDisplay->update();
	}
	else {
		this->playerTwoChoice = this->matrix->getPlayerTwoChoice();
		this->playerTwoDisplay->update(this->playerTwoChoice);
	}
	
}

void SceneMenu::render()
{
	this->window->clear();
	this->window->draw(this->menuScreenSprite);
	this->matrix->render(this->window);
	this->playerOneDisplay->render(this->window);
	this->playerTwoDisplay->render(this->window);
	this->window->draw(this->PickYour);
	this->window->draw(this->player1);
	this->window->draw(this->player2);
	this->window->display();
}

void SceneMenu::initCharactersMatrix(std::string textureName)
{
	this->matrix = std::make_unique<SelGUIElementsMatrix>(textureName, 3, 3, 200, 200);
}

void SceneMenu::initBackground(std::string textureName)
{
	this->menuScreenTexture = std::make_unique<sf::Texture>();
	if (!this->menuScreenTexture->loadFromFile("./Textures/" + textureName)) {
		std::cout << " ! ERR: SCENEMENU: could not load menu img" << std::endl;
	}
	//set load to loaded texture
	this->menuScreenSprite.setTexture(*(this->menuScreenTexture));
}

void SceneMenu::initText()
{
	this->font = std::make_unique<sf::Font>();
	if (!this->font->loadFromFile("./Textures/font.ttf")) {
		std::cout << "Czcionka nie wczytana";
	}
	this->PickYour.setFont(*this->font);
	this->PickYour.setString("CHOOSE YOUR FIGHTER");
	this->PickYour.setCharacterSize(50);
	this->PickYour.setFillColor(sf::Color::Yellow);
	this->PickYour.setStyle(sf::Text::Bold);
	this->PickYour.setPosition(640 - this->PickYour.getLocalBounds().width / 2, 20.f);

	this->player1.setFont(*this->font);
	this->player1.setString("Player One");
	this->player1.setCharacterSize(25);
	this->player1.setFillColor(sf::Color::Red);
	this->player1.setStyle(sf::Text::Bold);
	this->player1.setPosition(15, 120.f);

	this->player2.setFont(*this->font);
	this->player2.setString("Player Two");
	this->player2.setCharacterSize(25);
	this->player2.setFillColor(sf::Color::Blue);
	this->player2.setStyle(sf::Text::Bold);
	this->player2.setPosition(1280-this->player1.getLocalBounds().width-20, 120.f);
}

void SceneMenu::setAreCharactersPicked(bool value)
{
	this->arePicked = value;
}

void SceneMenu::initVariables()
{
	this->arePicked = false;
	this->switchingLimit = 3;
	this->sincePlayerOneSwitched = 0;
	this->sincePlayerTwoSwitched = 0;
}
