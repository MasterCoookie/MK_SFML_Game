#include "GameEngine.h"

GameEngine::GameEngine() {
	//not really used
	this->initWindow();
	this->initVariables();
}

GameEngine::GameEngine(sf::RenderWindow* win) {
	//all inits
	this->window = win;
	this->initVariables();
	this->initWorld("bcg.png");
}

GameEngine::~GameEngine() { 
	delete this->window;
}

void GameEngine::run() {
	//gameloop
	while (this->window->isOpen()) {
		this->pollEvents();
		this->update();
		this->render();
	}
}

std::vector<std::string> GameEngine::getResult()
{
	std::vector<std::string> vec={""};
	return vec;
}

void GameEngine::setInterSceneValues(std::vector<std::string>& vec) {
	this->initPlayers(vec[0], vec[1]);
}

void GameEngine::initVariables() {

}

void GameEngine::initWorld(std::string textureName) {
	//load texture from file
	if (!this->worldBcgTex.loadFromFile("./Textures/" + textureName)) {
		std::cout << " ! ERR: GAMEENGINE::INITWORLD: could not load bcg img" << std::endl;
	}
	//set bcg to loaded texture
	this->worldBcg.setTexture(this->worldBcgTex);
}

void GameEngine::initPlayers(std::string p1charName, std::string p2charName) {
	//create players, based on character names
	this->player1 = new Player(p1charName);
	this->player2 = new Player(p2charName);

	//place players in the right position
	this->player1->setPosition(200.f, 800.f - this->player1->getBounds().height);
	this->player1->setRightFacing(true);
	this->player2->setPosition(1080.f - this->player2->getBounds().width, 800.f - this->player2->getBounds().height);
	this->player2->setRightFacing(false);
}

void GameEngine::initWindow() {
	//initializes window with set params
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 960), "Mortul Kombet", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void GameEngine::pollEvents() {
	//eventy - exiting game
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
		}
	}
}

void GameEngine::update() {
	//TMP
	this->player1->update();

	this->updateInput();
	//move players
	if (this->player1->canMove()) {
		this->player1->move();
		this->player1->jump();
		this->player1->duck();
	}
	if (this->player2->canMove()) {
		this->player2->move();
		this->player2->jump();
		this->player2->duck();
	}
	this->player1->updateMovement();
	this->player2->updateMovement();
	//TODO - attack

	this->updatePlayersCross();

	//reset movementMatrixes
	this->player1->resetMovementMatrix();
	this->player2->resetMovementMatrix();
}

void GameEngine::updateInput() {
	//check for attack codes, if none, potentially move player

	//player1 starts
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
		//TODO - translate attacks
	}
	else {
		this->player1->setMovementMatrix(
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->player1->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !this->player1->rightFacing()),
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->player1->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !this->player1->rightFacing()),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S),
			0, 0, 0
		);
	}
	//player1 ends
	//player2 starts
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
		//TODO - translate attacks
	}
	else {
		this->player2->setMovementMatrix(
			((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) && !this->player2->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->player2->rightFacing()),
			((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) && !this->player2->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && this->player2->rightFacing()),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I),
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K),
			0, 0, 0
		);
	}
	//player2 ends
}

void GameEngine::updatePlayersCross() {
	//cross from right
	if (this->player1->rightFacing() && (this->player1->getPosition().x > this->player2->getPosition().x - this->player2->getBounds().width)) {
		//cross happended, switch player facing
		this->player1->setRightFacing(false);
		this->player2->setRightFacing(true);
	}
	//cross from left													// the spite is scaled on negative, so his x has to be lowered by its width
	if (this->player2->rightFacing() && (this->player2->getPosition().x > this->player1->getPosition().x - this->player1->getBounds().width)) {
		//cross happended, switch player facing
		this->player2->setRightFacing(false);
		this->player1->setRightFacing(true);
	}
}

void GameEngine::render() {
	//clear old render first
	this->window->clear();

	//draw stuf here
	this->renderWorld();

	this->player1->render(this->window);
	this->player2->render(this->window);


	//display stuff
	this->window->display();
}

void GameEngine::renderWorld() {
	this->window->draw(this->worldBcg);
}
