#include "GameEngine.h"

import async_functions;

GameEngine::GameEngine() {
	//not really used
	this->initWindow();
	this->initVariables();
}

GameEngine::GameEngine(std::shared_ptr<sf::RenderWindow> win) {
	//all inits
	this->window = win;
	this->initView();
	this->initVariables();
	this->initWorld("bcg.png");
	this->initArena();
	//this->initHealthBars();
	this->initWinCircles();
}

GameEngine::~GameEngine() { 
	
}

void GameEngine::run() {
	//gameloop
	while (this->window->isOpen() && this->isRunning) {
		this->pollEvents();
		this->update();
		this->render();
	}
}

std::vector<std::string> GameEngine::getResult()
{
	std::vector<std::string> vec={this->result, this->player1->getCharName(),this->player2->getCharName()};
	return vec;
}

void GameEngine::setInterSceneValues(std::vector<std::string>& vec) {
	this->initPlayers(vec[0], vec[1]);
}

void GameEngine::initVariables() {
	this->isRunning = true;
	this->result = "";
	this->matchManager = std::make_unique < MatchManager >();
	this->initTimer();
	this->initGUIMsg();
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
	//this->player1 = new Player(p1charName); 	 depraciated
	//this->player2 = new Player(p2charName);	 depraciated
	// 
	//load characters asynchronously
	LoadingScreen ldscreen(this->window, p1charName, p2charName);
	ldscreen.loadPlayers();
	this->player1 = ldscreen.getPlayerOne();
	this->player2 = ldscreen.getPlayerTwo();
	this->initHealthBars(this->player1->getCharGUIName(), this->player2->getCharGUIName());

	//place players in the right position
	this->initPlayersPos();

	this->view->move(640.f, 0.f);
	this->window->setView(*this->view);
}

void GameEngine::initHealthBars(std::string name1, std::string name2)
{
	this->hbplayer1 = std::make_unique<HealthBar>(true, name1);
	this->hbplayer2 = std::make_unique<HealthBar>(false, name2);
}

void GameEngine::initTimer()
{
	this->timerGUI = std::make_unique < Timer>();
}

void GameEngine::initWinCircles()
{
	this->wcplayer1 = std::make_unique < WinCircle>(true);
	this->wcplayer2 = std::make_unique < WinCircle>(false);

}

void GameEngine::initGUIMsg()
{
	this->msg = std::make_unique < GUIMessage> ();
}

void GameEngine::initPlayersPos() {
	this->player1->setRightFacing(true);
	this->player1->setPosition(840.f, 800.f - this->player1->getBounds().height);
	this->player2->setRightFacing(false);
	this->player2->setPosition(1720.f, 800.f - this->player2->getBounds().height);
}

void GameEngine::initArena()
{
	this->arena = std::make_unique<Arena>();
}

void GameEngine::initWindow() {
	//initializes window with set params
	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 960), "Mortul Kombet", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(30);
	this->window->setVerticalSyncEnabled(false);
}

void GameEngine::initView() {
	this->view = std::make_shared <sf::View>(sf::FloatRect(0.f, 0.f, 1280.f, 960.f));
	this->window->setView(*this->view);
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
			if (this->matchManager->hasMatchEnded()) {
				if (e.Event::key.code == sf::Keyboard::F2) {
					//rematch here
					this->isRunning = false;
					this->result = "F2";
					std::cout << "Rematch\n";
				} else if (e.Event::key.code == sf::Keyboard::F3) {
					//change chars here
					this->result = "F3";
					this->isRunning = false;
				}
			} else {
				//reading attack inputs
				this->player1->setMovementMatrix((e.Event::key.code == sf::Keyboard::F), (e.Event::key.code == sf::Keyboard::G), (e.Event::key.code == sf::Keyboard::H));
				this->player2->setMovementMatrix((e.Event::key.code == sf::Keyboard::Left), (e.Event::key.code == sf::Keyboard::Down), (e.Event::key.code == sf::Keyboard::Right));
			}
		}
	}
}

void GameEngine::printDebug(){
	//use wherever needed
	std::cout << "P1 x: " << this->player1->getPosition().x << "\n";
	std::cout << "P2 x: " << this->player2->getPosition().x << "\n";
}

void GameEngine::update() {
	this->updateMatchManager();

	this->player1->updateStagger();
	this->player2->updateStagger();
	//this->updateInput();
	if (!this->matchManager->getAreInputsBlocked()) {
		this->matchManager->update();


		std::thread read_movement(async_read_input, this);
		std::thread async_movement(async_move_players, this->player1, this->player2);

		read_movement.join();
		async_movement.join();

		this->updatePlayersScreenCollision();

		this->updateView();

		this->updatePlayersMovement();

		this->updatePlayersAttacks();
	}
	else {
		this->player1->updateRecovery();
		this->player2->updateRecovery();

		this->player1->updateMovement();
		this->player2->updateMovement();
	}
	
	std::thread recovery_th_p1(async_recovery, this->player1);
	std::thread recovery_th_p2(async_recovery, this->player2);

	recovery_th_p1.join();
	recovery_th_p2.join();

	this->updatePlayersCross();
	//this->printDebug();
	this->updatePlayersCollision();

	this->updateAttacksCollision();

	std::thread animation_th_p1(async_animation, this->player1);
	std::thread animation_th_p2(async_animation, this->player2);
	
	animation_th_p1.join();
	animation_th_p2.join();
	this->hbplayer1->update(this->player1->getHp());
	this->hbplayer2->update(this->player2->getHp());
	this->msg->updateMessage(this->matchManager->getMsg(),this->view);

}

void GameEngine::updateInput() {
	//blocking
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) && this->player1->getState() != State::HIT_STAGGERED && this->player1->getState() != State::BLOCK_STAGGERED && this->player1->getBodyPosition() != Position::AIRBORNE) {
		this->player1->block();
	} else if (this->player1->getState() == State::BLOCKING) {
		this->player1->dropBlock(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->player2->getState() != State::HIT_STAGGERED && this->player2->getState() != State::BLOCK_STAGGERED && this->player2->getBodyPosition() != Position::AIRBORNE) {
		this->player2->block();
	}
	else if (this->player2->getState() == State::BLOCKING) {
		this->player2->dropBlock(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K));
	}

	//check for attack codes, if none, potentially move player
	this->player1->setMovementMatrix(
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->player1->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !this->player1->rightFacing()),
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->player1->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !this->player1->rightFacing()),
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W),
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
	);
	this->player2->setMovementMatrix(
		((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) && !this->player2->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && this->player2->rightFacing()),
		((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) && !this->player2->rightFacing()) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && this->player2->rightFacing()),
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I),
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)
	);
	//player2 ends
}

void GameEngine::updatePlayersCross() {
	//cross from right
	if (this->player1->getBodyPosition() != Position::LYING && this->player2->getBodyPosition() != Position::LYING) {
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
	
}

void GameEngine::updatePlayersCollision() {
	//only resolve player to player collision when players are not jumping
	if (this->player1->getBodyPosition() != Position::AIRBORNE && this->player2->getBodyPosition() != Position::AIRBORNE) {
		//check players for collision
		if (this->player1->getBounds().intersects(this->player2->getBounds())) {
			float pos_diff = 0.f;
			//position calculations differ depending on orientation
			if (this->player1->rightFacing()) {
				//calculate difference																						devide to move both players (pushing)
				pos_diff = (this->player1->getPosition().x + 2 * this->player1->getBounds().width - this->player2->getPosition().x) / 2.f;
				//move players (also differs on oreintation)
				this->player1->GameObject::move(-pos_diff, 0.f);
				this->player2->GameObject::move(pos_diff, 0.f);
			} else {
				pos_diff = (this->player2->getPosition().x + 2 * this->player2->getBounds().width - this->player1->getPosition().x) / 2.f;
				this->player1->GameObject::move(pos_diff, 0.f);
				this->player2->GameObject::move(-pos_diff, 0.f);
			}
		}
	}
}

void GameEngine::updatePlayersScreenCollision() {
	if (this->player1->getPosition().x < this->view->getCenter().x - 640.f) {
		this->player1->setPosition(this->view->getCenter().x - 640.f, this->player1->getPosition().y);
	}
	if (this->player2->getPosition().x > this->view->getCenter().x + 640.f) {
		this->player2->setPosition(this->view->getCenter().x + 640.f, this->player2->getPosition().y);
	}

	if (this->player2->getPosition().x < this->view->getCenter().x - 640.f) {
		this->player2->setPosition(this->view->getCenter().x - 640.f, this->player2->getPosition().y);
	}
	if (this->player1->getPosition().x > this->view->getCenter().x + 640.f) {
		this->player1->setPosition(this->view->getCenter().x + 640.f, this->player1->getPosition().y);
	}
}

void GameEngine::updateAttacksCollision() {
	if (this->player1->getCurrentAttack().getIsActive() && this->player1->getCurrentAttack().getBounds().intersects(this->player2->getBounds())) {
		this->player2->takeHit(this->player1->getCurrentAttack());
		if (!this->matchManager->isRoundResetPlanned() && this->player2->getHp() <= 0) {
			this->player1->winRound();
			this->player2->looseRound();
			this->wcplayer1->update();
			this->matchManager->endRound(this->player1->getCharGUIName());
			this->player2->blockGetup();
			if (this->player1->getRoundsWon() >= 2) {
				this->matchManager->endMatch();
			}
		}
	}

	if (this->player2->getCurrentAttack().getIsActive() && this->player2->getCurrentAttack().getBounds().intersects(this->player1->getBounds())) {
		this->player1->takeHit(this->player2->getCurrentAttack());
		if (!this->matchManager->isRoundResetPlanned() && this->player1->getHp() <= 0) {
			this->player2->winRound();
			this->player1->looseRound();
			this->wcplayer2->update();
			this->matchManager->endRound(this->player2->getCharGUIName());
			this->player1->blockGetup();
			if (this->player2->getRoundsWon() >= 2) {
				this->matchManager->endMatch();
			}
		}
	}
}

void GameEngine::updateView() {
	float dist_between_players;
	if (this->player1->rightFacing()) {
		dist_between_players = this->player2->getPosition().x - this->player2->getBounds().width - this->player1->getPosition().x;
	} else {
		dist_between_players = this->player1->getPosition().x - this->player1->getBounds().width - this->player2->getPosition().x;
	}
	
	if (!update_view(this, this->player1, this->player2, this->view, dist_between_players)) {
		update_view(this, this->player2, this->player1, this->view, dist_between_players);
	}
	this->window->setView(*this->view);
}

void GameEngine::updateMatchManager() {
	if (this->matchManager->getAreInputsBlocked()) {
		if (this->matchManager->isRoundResetPlanned()) {
			if (this->matchManager->resetNow()) {
				this->resetRound();
				this->matchManager->beginRound();
			}
		}
	}

	if (this->matchManager->getRoundTimer().asSeconds() <= 0) {
		//this->resetRound();
		const float p1_hp = this->player1->getHp();
		const float p2_hp = this->player2->getHp();
		if (p1_hp > p2_hp) {
			this->player1->winRound();
			this->player2->looseRound();
			this->wcplayer1->update();
			this->matchManager->endRound(this->player1->getCharGUIName());
			this->player2->blockGetup();
			if (this->player1->getRoundsWon() >= 2) {
				this->matchManager->endMatch();
			}
		} else if (p1_hp < p2_hp) {
			this->player2->winRound();
			this->player1->looseRound();
			this->wcplayer2->update();
			this->matchManager->endRound(this->player2->getCharGUIName());
			this->player1->blockGetup();
			if (this->player2->getRoundsWon() >= 2) {
				this->matchManager->endMatch();
			}
		} else {
			this->player1->winRound();
			this->player2->winRound();
			this->matchManager->endRound("Nobody");
			this->player1->blockGetup();
			this->player2->blockGetup();
		}
	}
	this->timerGUI->update(this->matchManager->getRoundTimer());
}

void GameEngine::updatePlayersMovement() {
	if (this->player1->getState() != State::BLOCKING) {
		this->player1->updateMovement();
	}

	if (this->player2->getState() != State::BLOCKING) {
		this->player2->updateMovement();
	}
}

void GameEngine::updatePlayersAttacks() {
	if (this->player1->canAttack() && this->player1->selectAttack()) {
		this->player1->attack();
	}
	else {
		this->player1->updateAttack();
	}

	if (this->player2->canAttack() && this->player2->selectAttack()) {
		this->player2->attack();
	}
	else {
		this->player2->updateAttack();
	}
}

void GameEngine::moveGUIElements(float offsetX, float offsetY)
{
	this->hbplayer1->move(offsetX, offsetY);
	this->hbplayer2->move(offsetX, offsetY);
	this->timerGUI->move(offsetX, offsetY);
	this->wcplayer1->move(offsetX, offsetY);
	this->wcplayer2->move(offsetX, offsetY);
	this->msg->move(offsetX, offsetY);
}

void GameEngine::resetRound() {
	this->player1->reset();
	this->player2->reset();
	this->initPlayersPos();
	this->view->setCenter(1280.f, this->view->getCenter().y);
	this->window->setView(*this->view);
	this->hbplayer1->reset();
	this->hbplayer2->reset();
	this->timerGUI->reset();
	this->wcplayer1->reset();
	this->wcplayer2->reset();
	this->arena->reset();
	this->matchManager->resetRoundTimer();
	std::cout << "Round ended!\n";
	 
}

void GameEngine::render() {
	//clear old render first
	this->window->clear();

	//draw stuf here
	this->renderWorld();

	this->player1->render(this->window);
	this->player2->render(this->window);

	this->arena->render(this->window);

	this->hbplayer1->render(this->window);
	this->hbplayer2->render(this->window);

	this->timerGUI->render(this->window);

	this->wcplayer1->render(this->window);
	this->wcplayer2->render(this->window);

	this->msg->render(this->window);

	//display stuff
	this->window->display();
}

void GameEngine::renderWorld() {
	this->window->draw(this->worldBcg);
}
