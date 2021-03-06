#include "Player.h"

import async_functions;

Player::Player() {
	this->initVariables();
}

Player::Player(std::string _charName) {
	this->charName = _charName;
	this->initGUIName();
	std::thread async_init_variables(init_gameobject_variables, this);
	// init player baset on character name
	this->GameObject::initTexture("./Characters/" + _charName + "/standing.png");
	this->initSprite(this->textureRect);
	this->animator = std::make_shared<Animator>(this->textureRect, 1500, 375, AnimationType::STANDING, true, true);
	this->movesMatrix = std::make_shared <AttackMovesMatrix>(_charName);
	async_init_variables.join();
}

Player::~Player() {
	
}

void Player::setRightFacing(bool facing) {
	//change direction in which player is facing
	this->isRightFacing = facing;
	//reverse player sprite
	if (facing && this->sprite.getScale().x < 0) {
		this->sprite.scale(-1.f, 1.f);
		this->sprite.move(-this->getBounds().width, 0);
	} else if(!facing && this->sprite.getScale().x >= 0) {
		this->sprite.scale(-1.f, 1.f);
		this->sprite.move(this->getBounds().width, 0);
	}
}

void Player::setMovementMatrix(bool lHand, bool rHand, bool kick) {
	this->movementMatrix[4] = lHand;
	this->movementMatrix[5] = rHand;
	this->movementMatrix[6] = kick;
}

void Player::setMovementMatrix(bool forward, bool back, bool up, bool down) {
	this->movementMatrix[0] = forward;
	this->movementMatrix[1] = back;
	this->movementMatrix[2] = up;
	this->movementMatrix[3] = down;
}

void Player::setMovementMatrix(bool forward, bool back, bool up, bool down, bool lHand, bool rHand, bool kick) {
	this->movementMatrix[0] = forward;
	this->movementMatrix[1] = back;
	this->movementMatrix[2] = up;
	this->movementMatrix[3] = down;
	this->movementMatrix[4] = lHand;
	this->movementMatrix[5] = rHand;
	this->movementMatrix[6] = kick;
}

void Player::resetMovementMatrix() {
	//used after movement
	memset(this->movementMatrix, 0, 7);
}

void Player::setState(const State& state) {
	this->state = state;
}

void Player::winRound() {
	++this->roundsWon;
}

void Player::looseRound() {

}

void Player::blockGetup() {
	this->getupBlocked = true;
}

void Player::move() {
	const int movementSpeed = 14;
	//move the player, dependent on direction its facing
	if (this->isRightFacing) {
		this->sprite.move(static_cast<float>(this->movementMatrix[0] * movementSpeed), 0);
		this->sprite.move(static_cast<float>(-(this->movementMatrix[1] * movementSpeed)), 0);
	} else {
		this->sprite.move(static_cast<float>(-(this->movementMatrix[0] * movementSpeed)), 0);
		this->sprite.move(static_cast<float>(this->movementMatrix[1] * movementSpeed), 0);
	}
}

void Player::jump() {
	//check if player is pressing up arrow
	if (this->movementMatrix[2]) {
		//add upwards momentum
		this->yAxisMomentum = -55.f;
		//change pos
		this->position = Position::AIRBORNE;
		//change texture
		this->sprite.setTexture(*this->playerTextures.find("jumping")->second, true);

		//move up ??
		//this->setPosition(this->getPosition().x, this->getPosition().y - 150.f);
		//if the player is also pressing dir arrow, add forwad x momentum
		const float baseXMomentum = 20.f;
		if (this->movementMatrix[0]) {			
			//bcs of +=/-= both keys will cancell eachother out
			
			if (this->isRightFacing) {
				this->xAxisMomentum += baseXMomentum;
			}
			else {
				this->xAxisMomentum -= baseXMomentum;
			}
		}
		//if the player is also pressing dir arrow, add back x momentum
		if (this->movementMatrix[1]) {
			if (this->isRightFacing) {
				this->xAxisMomentum -= baseXMomentum;
			}
			else {
				this->xAxisMomentum += baseXMomentum;
			}
		}
	}
}

void Player::duck() {
	if (this->movementMatrix[3] && this->position != Position::DUCKING) {
		//change pos
		this->position = Position::DUCKING;
		//change texture
		this->sprite.setTexture(*this->playerTextures.find("ducking")->second, true);
		// move down
		this->setPosition(this->getPosition().x, 550.f);
	}
}

void Player::block() {
	
	if (this->position == Position::STANDING) {
		this->state = State::BLOCKING;
		this->setPosition(this->getPosition().x, 425.f);
		this->sprite.setTexture(*this->playerTextures.find("blocking")->second, true);
	} else if (this->position == Position::DUCKING) {
		this->state = State::BLOCKING;
		this->setPosition(this->getPosition().x, 550.f);
		this->sprite.setTexture(*this->playerTextures.find("ducking_block")->second, true);
	}
}

void Player::dropBlock(const bool continueDuckin) {
	this->state = State::IDLE;
	if (continueDuckin) {
		this->sprite.setTexture(*this->playerTextures.find("ducking")->second);
	} else {
		this->sprite.setTexture(*(this->texture));
		this->initSprite(this->textureRect);
	}
}

void Player::stagger(const State state, const float frames) {
	this->state = state;
	this->staggerFrames = frames;
}

void Player::recover(const float frames) {
	this->recoveryFrames = frames;
}

bool Player::selectAttack() {
	if (this->state != State::ATTACKING && (this->movementMatrix[4] || this->movementMatrix[5] || this->movementMatrix[6])) {

		if (this->movesMatrix->doesAttackMoveExist(this->movementMatrix)) {
			this->currentAttack = AttackMove(this->movesMatrix->getAttackMove(this->movementMatrix), this->getPosition(), this->isRightFacing);
			this->state = State::ATTACKING;
			return true;
		}
	}
	return false;
}

void Player::attack() {
	if ((this->movementMatrix[4] || this->movementMatrix[5] || this->movementMatrix[6])) {
		if (this->selectAttack()) {}
	}
}

void Player::takeHit(AttackMove& hitBy) {
	if (!hitBy.getWasHitRegistered() && !hitBy.getWasBlockRegistered()) {
		if (this->state != State::GETTING_UP || this->position != Position::LYING) {
			if (this->wasAttackBlocked(hitBy)) {
				std::cout << "Blocked\n";
				hitBy.registerBlock();
				this->hp -= hitBy.getDmg() / 10.f;

				this->stagger(State::BLOCK_STAGGERED, static_cast<float>(hitBy.getOnBlockStagger()));
			}
			else {
				this->hp -= hitBy.getDmg();
				//TMP
				std::cout << this->hp << "\n";
				this->xAxisMomentum = static_cast<float>(hitBy.getKnockback());
				if (hitBy.getKnockup()) {
					this->position = Position::AIRBORNE;
					this->yAxisMomentum = static_cast<float>(hitBy.getKnockup());
					this->stagger(State::HIT_STAGGERED, static_cast<float>(hitBy.getOnHitStagger()));
				}
				else {
					this->stagger(State::HIT_STAGGERED, static_cast<float>(hitBy.getOnHitStagger()));
				}
				hitBy.registerHit();
			}
		}
	}
	
}

void Player::reset() {
	this->hp = hpMax;
	this->position = Position::STANDING;
	this->state = State::IDLE;
	this->xAxisMomentum = 0;
	this->yAxisMomentum = 0;
	this->getupBlocked = false;
	this->staggerFrames = 0.f;
	this->recoveryFrames = 0.f;
	this->recoveryFrames = 10.f;
	this->textureRect = std::make_shared<sf::IntRect>(0, 0, 150, 375);
	 
	this->animator = std::make_shared<Animator>(this->textureRect, 1500, 375, AnimationType::STANDING, true, true);
	this->initSprite(this->textureRect);
}

const bool Player::rightFacing() {
	return this->isRightFacing;
}

const bool Player::getMovementMatrix() {
	return this->movementMatrix;
}

const Position Player::getBodyPosition() {
	return this->position;
}

const State Player::getState() {
	return this->state;
}

AttackMove& Player::getCurrentAttack() {
	return this->currentAttack;
}

const int Player::getRoundsWon() {
	return this->roundsWon;
}

const float Player::getHp() {
	return this->hp;
}

const std::string Player::getCharName() {
	return this->charName;
}

const std::string Player::getCharGUIName()
{
	return this->charGUIname;
}

void Player::update() {
	std::cout << this->getPosition().y << "\n";
}

void Player::render(std::shared_ptr<sf::RenderTarget> win) {
	win->draw(this->sprite);
	if (this->state == State::ATTACKING) {
		this->currentAttack.render(win);
	}
}

bool Player::canMove() {
	return (this->position == Position::STANDING && this->state == State::IDLE);
}

bool Player::canAttack() {
	return (this->state == State::IDLE && this->position != Position::AIRBORNE);
}

void Player::initVariables() {
	this->position = Position::STANDING;
	this->state = State::IDLE;
	this->xAxisMomentum = 0;
	this->yAxisMomentum = 0;
	this->hpMax = 100.f;
	this->hp = hpMax;
	this->staggerFrames = 0.f;
	this->recoveryFrames = 0.f;
	this->textureRect = std::make_shared<sf::IntRect>(0, 0, 150, 375);
	this->roundsWon = 0;
	this->getUpFrames = 10;
	this->getupBlocked = false;

	this->playerTextures = {
		{ "ducking", nullptr },
		{ "jumping", nullptr },
		{ "jumping_f", nullptr },
		{ "jumping_b", nullptr },
		{ "walking_b", nullptr },
		{ "walking_f", nullptr },
		{ "blocking", nullptr },
		{ "ducking_block", nullptr },
		{ "lying", nullptr },
		{ "getting_up", nullptr },
		{ "falling", nullptr },
	};
	this->initTexturesMap();
}

void Player::initGUIName()
{
	std::string read, toSet = " ";
	std::string path = ".\\Characters\\" + this->charName + "\\charname.txt";
	std::ifstream myFile;
	myFile.open(path);
	if (myFile.is_open()) {
		while (myFile >> read) {
			toSet += read;
			toSet += " ";
		}

		myFile.close();
	}
	this->charGUIname = toSet;
}

void Player::initTexturesMap() {
	//auto names = std::views::keys(this->playerTextures);
	for (auto& tex : this->playerTextures) {
		this->initTexture(tex.second, ("./Characters/" + this->charName + "/" + tex.first + ".png"));
	}
	//ranges to check if some textures didnt load
	auto didLoad = [](const std::shared_ptr<sf::Texture> pointer) { return pointer == nullptr; };
	for (const auto& val : std::views::values(this->playerTextures) | std::views::filter(didLoad)) {
		std::cout << "PLAYER::initTexturesMap() CRITCAL ERROR: nullptr in map!\n";
	}
}

bool Player::wasAttackBlocked(const AttackMove& hitBy) {
	if (this->state != State::BLOCKING && this->state != State::BLOCK_STAGGERED) {
		return false;
	} else if(hitBy.getTargetHeight() == TargetHeight::LOW && this->position == Position::STANDING) {
		return false;
	} else if (hitBy.getTargetHeight() == TargetHeight::OVERHEAD && this->position == Position::DUCKING) {
		return false;
	}
	return true;
}

void Player::updateLanding() {
	const unsigned int landing_border = (this->state != State::HIT_STAGGERED) ? 425 : 655;
	//check for landing
	if (this->getPosition().y > landing_border) {
		this->yAxisMomentum = 0;
		this->xAxisMomentum = 0;
		if (this->position == Position::AIRBORNE) {
			if (this->state == State::HIT_STAGGERED) {
				this->position = Position::LYING;


				this->textureRect = std::make_shared<sf::IntRect>(0, 0, 300, 150);
				this->initSprite(*(this->playerTextures.find("lying")->second), this->textureRect);

				this->setPosition(this->getPosition().x, 650);
			}
			else {
				this->position = Position::STANDING;
				this->setPosition(this->getPosition().x, 425);
			}

		}
	}
}

void Player::updateDuck() {
	//check if still ducking
	if (!this->movementMatrix[3] && this->position == Position::DUCKING) {
		//stand up if button was released
		this->position = Position::STANDING;
		this->sprite.setTexture(*(this->texture), true);
		this->initSprite(this->textureRect);
		this->setPosition(this->getPosition().x, this->getPosition().y - 125.f);
	}
}


void Player::updateMovement() {
	//move for momentum
	GameObject::move(xAxisMomentum, yAxisMomentum);
	// gravity
	this->yAxisMomentum += 4.5f;

	this->updateLanding();

	this->updateDuck();
}

void Player::updateAttack() {
	if (this->state == State::ATTACKING) {
		this->currentAttack.update();
		if (this->currentAttack.getHasEnded() && this->recoveryFrames <= 0.f) {
			this->recover(this->currentAttack.getRecovery());
		}
	}
}

void Player::updateStagger() {
	if (!(this->position == Position::AIRBORNE)) {
		if (this->staggerFrames > 0.f) {
			--this->staggerFrames;
		}
		else {
			if (this->state == State::HIT_STAGGERED) {
				if (this->position == Position::LYING) {
					this->state = State::GETTING_UP;
				} else {
					this->state = State::IDLE;
				}
			}
			else if (this->state == State::BLOCK_STAGGERED) {
				this->dropBlock(this->movementMatrix[3]);
			}
		}
		this->updateGetUp();
	}
}

void Player::updateGetUp() {
	if (!this->getupBlocked && this->state == State::GETTING_UP) {
		if (--this->getUpFrames < 0) {
			this->state = State::IDLE;
			this->position = Position::DUCKING;
			this->getUpFrames = 10;
		}
	}
}

void Player::updateRecovery() {
	if (this->state == State::ATTACKING && this->currentAttack.getHasEnded()) {
		if (this->recoveryFrames > 0.f) {
			if (--this->recoveryFrames <= 0) {
				this->state = State::IDLE;
			}
		}
	}
}

void Player::updateAnimation() {
	if (this->state == State::IDLE && this->position == Position::STANDING && this->movementMatrix[0]) {
		if (this->animator != nullptr && this->animator->getCurrAnimationType() == AnimationType::WALKING_F) {
			//continue animate walking forward
			this->animator->update();
			this->initSprite(*this->playerTextures.find("walking_f")->second, this->textureRect);
		} else {
			//start animating walking forward			
			this->textureRect = std::make_shared<sf::IntRect>(0, 0, 150, 375);
			int tex_size = (* (this->playerTextures.find("walking_f")->second)).getSize().x;
			 
			this->animator = std::make_shared<Animator>(this->textureRect, tex_size, 375, AnimationType::WALKING_F, true, false);
			this->initSprite(this->textureRect);
			this->setPosition(this->getPosition().x, 425.f);
		}
	} else if (this->state == State::IDLE && this->position == Position::STANDING && this->movementMatrix[1]) {
		if (this->animator != nullptr && this->animator->getCurrAnimationType() == AnimationType::WALKING_B) {
			//continue animate walking forward
			this->animator->update();
			this->initSprite(*this->playerTextures.find("walking_b")->second, this->textureRect);
		} else {
			//start animating walking forward

			this->textureRect = std::make_shared<sf::IntRect>(0, 0, 150, 375);
			int tex_size = (*(this->playerTextures.find("walking_b")->second)).getSize().x;

			this->animator = std::make_shared<Animator>(this->textureRect, tex_size, 375, AnimationType::WALKING_B, true, false);
			this->initSprite(this->textureRect);
			this->setPosition(this->getPosition().x, 425.f);
		}
	}
	else if(this->state == State::IDLE && this->position == Position::AIRBORNE) {
			//continue animate jumping forward
			if (this->animator != nullptr && this->animator->getCurrAnimationType() == AnimationType::JUMPING) {
				this->animator->update();
				this->initSprite(*this->playerTextures.find(this->lockedAnimation)->second, this->textureRect);
		} else {
			//start animating jumping
			if (this->movementMatrix[0] || this->movementMatrix[1]) {
				this->textureRect = std::make_shared<sf::IntRect>(0, 0, 175, 175);
				int tex_size = (*(this->playerTextures.find("jumping_f")->second)).getSize().x;

				this->animator = std::make_shared<Animator>(this->textureRect, tex_size, 175, AnimationType::JUMPING, true, false, 175);
				if (this->movementMatrix[0]) {
					this->lockedAnimation = "jumping_f";
				} else {
					this->lockedAnimation = "jumping_b";
				}
			}
		}
	} else if (this->state == State::ATTACKING) {
		if (this->animator != nullptr && this->animator->getCurrAnimationType() == AnimationType::ATTACKING) {
			//continue animate attacking
			this->animator->update();
			this->initSprite(*this->attackingTexture, this->textureRect);
		} else {
			this->textureRect = std::make_shared<sf::IntRect>(0, 0, 150, 375);
			 
			this->attackingTexture = this->currentAttack.getPlayerTexture();
			this->initSprite(*this->attackingTexture, this->textureRect);
			int maxW = 150 * (this->currentAttack.getAnimationLen()+1);
			this->animator = std::make_shared<Animator>(this->textureRect, maxW, 375, AnimationType::ATTACKING, false, false);
		}
	} else if (this->state == State::GETTING_UP) {
		if (this->animator != nullptr && this->animator->getCurrAnimationType() == AnimationType::GETTING_UP) {
			//continue animate getting up
			this->animator->update();
			this->initSprite(*this->playerTextures.find("getting_up")->second, this->textureRect);
		}
		else {
			//start getup animation
			if (!this->getupBlocked) {
				this->sprite.move(0.f, -50.f);

				this->textureRect = std::make_shared<sf::IntRect>(0, 0, 275, 200);

				this->initSprite(*this->playerTextures.find("getting_up")->second, this->textureRect);
				this->animator = std::make_shared<Animator>(this->textureRect, 2750, 200, AnimationType::GETTING_UP, false, false, 275);
			}			
		}
	} else if (this->state == State::HIT_STAGGERED && this->position == Position::AIRBORNE) {
		if (this->animator != nullptr && this->animator->getCurrAnimationType() == AnimationType::FALLING) {
			//continue animate falling
			this->animator->update();
			this->initSprite(*this->playerTextures.find("falling")->second, this->textureRect);
		} else {
			//start getup falling			
			this->textureRect = std::make_shared<sf::IntRect>(0, 0, 300, 150);
			 
			this->initSprite(*this->playerTextures.find("falling")->second, this->textureRect);
			int tex_size = (*(this->playerTextures.find("falling")->second)).getSize().x;
			this->animator = std::make_shared<Animator>(this->textureRect, tex_size, 150, AnimationType::FALLING, true, false, 300);
		}
	}
	else {
		if (this->state == State::IDLE && this->position == Position::STANDING) {
			if (this->animator != nullptr && this->animator->getCurrAnimationType() == AnimationType::STANDING) {
				//continue animate standing
				this->animator->update();
				this->initSprite(this->textureRect);
			} else {
				//start animating standing
				this->setPosition(this->getPosition().x, 425.f);
				
				this->textureRect = std::make_shared<sf::IntRect>(0, 0, 150, 375);
				 
				this->animator = std::make_shared<Animator>(this->textureRect, 1500, 375, AnimationType::STANDING, true, true);
				this->initSprite(this->textureRect);
			}
		}
	}
}
