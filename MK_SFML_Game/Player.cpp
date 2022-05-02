#include "Player.h"

Player::Player() {
	this->initVariables();
}

Player::Player(std::string charName) {
	this->initVariables();
	// init player baset on character name
	this->GameObject::initTexture("./Characters/" + charName + "/standing_1.png");
	this->GameObject::initTexture(this->walkingFTexture, "./Characters/" + charName + "/walking_f_1.png");
	this->GameObject::initTexture(this->walkingBTexture, "./Characters/" + charName + "/walking_b_1.png");
	this->initTexture(this->duckingTexture, "./Characters/" + charName + "/ducking.png");
	// TODO - create actual jumping texture
	this->initTexture(this->jumpingTexture, "./Characters/" + charName + "/ducking.png");
	this->initTexture(this->blockingTexture, "./Characters/" + charName + "/blocking.png");
	this->initTexture(this->blockingDuckTexture, "./Characters/" + charName + "/ducking_block.png");
	this->initSprite(this->textureRect);

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
	if (this->position == Position::STANDING) {
		this->sprite.setTexture(this->blockingTexture);
	} else {
		this->sprite.setTexture(this->blockingDuckTexture);
	}
}

void Player::dropBlock(const bool continueDuckin) {
	this->state = State::IDLE;
	if (continueDuckin) {
		this->sprite.setTexture(this->duckingTexture);
	} else {
		this->sprite.setTexture(this->texture);
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
	if (!hitBy.getWasHitRegistered() && !hitBy.getWasBlockRegistered()) {
		if (this->wasAttackBlocked(hitBy)) {
			std::cout << "Blocked\n";
			hitBy.registerBlock();
			this->hp -= hitBy.getDmg()/10.f;
			//TMP
			std::cout << this->hp << "\n";

			this->stagger(State::BLOCK_STAGGERED, hitBy.getOnBlockStagger());
		} else {
			this->hp -= hitBy.getDmg();
			//TMP
			std::cout << this->hp << "\n";
			this->xAxisMomentum = hitBy.getKnockback();
			if (hitBy.getKnockup()) {
				this->position = Position::AIRBORNE;
				this->yAxisMomentum = hitBy.getKnockup();
			}
			else {
				this->stagger(State::HIT_STAGGERED, hitBy.getOnHitStagger());
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
	this->staggerFrames = 0.f;
	this->recoveryFrames = 0.f;
	this->textureRect = new sf::IntRect(0, 0, 150, 375);
	this->animator = new Animator(this->textureRect, 1500, 375, AnimationType::STANDING, true);
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
			this->initSprite(this->textureRect);
			this->setPosition(this->getPosition().x, 425);
		}
	}

	//check if still ducking
	if (!this->movementMatrix[3] && this->position == Position::DUCKING) {
		//stand up if button was released
		this->position = Position::STANDING;
		this->sprite.setTexture(this->texture, true);
		this->initSprite(this->textureRect);
		this->setPosition(this->getPosition().x, this->getPosition().y - 150.f);
	}
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
	if (this->staggerFrames > 0.f) {
		//tmp
		//std::cout << this->staggerFrames << "\n";
		--this->staggerFrames;
	} else {
		if(this->state == State::HIT_STAGGERED) {
			this->state = State::IDLE;
		} else if(this->state == State::BLOCK_STAGGERED) {
			this->dropBlock(this->movementMatrix[3]);
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
		if (this->animator->getCurrAnimationType() == AnimationType::WALKING_F) {
			//continue animate walking forward
			this->animator->update();
			this->initSprite(this->walkingFTexture, this->textureRect);
		}
		else {
			//start animating walking forward
			delete this->animator;
			this->animator = new Animator(this->textureRect, 1800, 375, AnimationType::WALKING_F, true);
		}
	}
	else {
		if (this->state == State::IDLE && this->position == Position::STANDING) {
			if (this->animator->getCurrAnimationType() == AnimationType::STANDING) {
				//continue animate standing
				this->animator->update();
				this->initSprite(this->textureRect);
			}
			else {
				//start animating standing
				delete this->animator;
				this->animator = new Animator(this->textureRect, 1500, 375, AnimationType::STANDING, true);
			}
		}
	}
	
}
