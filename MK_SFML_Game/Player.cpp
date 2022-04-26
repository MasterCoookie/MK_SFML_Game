#include "Player.h"

Player::Player() {
	this->initVariables();
}

Player::Player(std::string charName) {
	this->initVariables();
	// init player baset on character name
	this->GameObject::initTexture("./Characters/" + charName + "/tex.png");
	this->initTexture(this->duckingTexture, "./Characters/" + charName + "/ducking.png");
	// TODO - create actual jumping texture
	this->initTexture(this->jumpingTexture, "./Characters/" + charName + "/ducking.png");
	this->initTexture(this->blockingTexture, "./Characters/" + charName + "/blocking.png");
	this->initSprite();

	this->charName = charName;
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

void Player::move() {
	const int movementSpeed = 14;
	//move the player, dependent on direction its facing
	if (this->isRightFacing) {
		this->sprite.move(this->movementMatrix[0] * movementSpeed, 0);
		this->sprite.move(-this->movementMatrix[1] * movementSpeed, 0);
	} else {
		this->sprite.move(-this->movementMatrix[0] * movementSpeed, 0);
		this->sprite.move(this->movementMatrix[1] * movementSpeed, 0);
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
		this->sprite.setTexture(this->duckingTexture, true);

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
		this->sprite.setTexture(this->duckingTexture, true);
		// move down
		this->setPosition(this->getPosition().x, this->getPosition().y + 150.f);
	}
}

void Player::block() {
	this->state = State::BLOCKING;
	this->sprite.setTexture(this->blockingTexture);
}

void Player::dropBlock() {
	this->state = State::IDLE;
	this->sprite.setTexture(this->texture);
}

bool Player::selectAttack() {
	//TMP
	//TODO - actually select an attack
	if (this->state != State::ATTACKING && this->movementMatrix[4] || this->movementMatrix[5] || this->movementMatrix[6]) {
		this->state = State::ATTACKING;
		this->currentAttack = AttackMove(this->getPosition(), 125, 50, this->isRightFacing, this->charName);
		return true;
	}
	return false;
}

void Player::attack() {
	if ((this->movementMatrix[4] || this->movementMatrix[5] || this->movementMatrix[6])) {
		if (this->selectAttack()) {
			//this->currentAttack.throwAttack();
			this->state = State::ATTACKING;
		}
	}
}

void Player::takeHit(AttackMove& hitBy) {
	if (!hitBy.getWasHitRegistered()) {
		if (this->state == State::BLOCKING) {
			//TODO - block, register that hit was blocked
		} else {
			//TODO resolve ducking and target
			this->hp -= hitBy.getDmg();
			//TMP
			std::cout << this->hp << "\n";
			this->xAxisMomentum = hitBy.getKnockback();
			if (hitBy.getKnockup()) {
				this->position = Position::AIRBORNE;
				this->yAxisMomentum = hitBy.getKnockup();
			}
			else {
				//todo - stagger attacked
			}


			hitBy.registerHit();
		}
	}
	
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

void Player::update() {
	std::cout << this->getPosition().y << "\n";
}

void Player::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
	if (this->state == State::ATTACKING) {
		this->currentAttack.render(target);
	}
}

bool Player::canMove() {
	//TODO - develop further
	return (this->position == Position::STANDING && this->state == State::IDLE);
}

bool Player::canAttack() {
	return this->state == State::IDLE;
}

void Player::initVariables() {
	this->position = Position::STANDING;
	this->state = State::IDLE;
	this->xAxisMomentum = 0;
	this->yAxisMomentum = 0;
	this->hpMax = 100.f;
	this->hp = hpMax;
}


void Player::updateMovement() {
	//move for momentum
	GameObject::move(xAxisMomentum, yAxisMomentum);
	// gravity
	this->yAxisMomentum += 4.5f;
		
	//check for landing
	if (this->getPosition().y >= 425) {
		this->yAxisMomentum = 0;
		this->xAxisMomentum = 0;
		if (this->position == Position::AIRBORNE) {
			this->position = Position::STANDING;
			this->sprite.setTexture(this->texture, true);
			this->setPosition(this->getPosition().x, 425);
		}
	}

	//check if still ducking
	if (!this->movementMatrix[3] && this->position == Position::DUCKING) {
		//stand up if button was released
		this->position = Position::STANDING;
		this->sprite.setTexture(this->texture, true);
		this->setPosition(this->getPosition().x, this->getPosition().y - 150.f);
	}
}

void Player::updateAttack() {
	if (this->state == State::ATTACKING) {
		this->currentAttack.update();
		if (this->currentAttack.getHasEnded()) {
			this->state = State::IDLE;
		}
	}
	
}
