#include "AttackMove.h"

AttackMove::AttackMove() {

}

AttackMove::AttackMove(const sf::Vector2f pos, float xSize, float ySize, bool isRightFacing) {
	this->initVariables();

	//USED ONLY IN DEBUG
	this->shape.setFillColor(sf::Color::Red);;
	this->shape.setSize(sf::Vector2f(xSize, ySize));
	//USED ONLY IN DEBUG ENDS

	// DO THIS IN OTHER CONSTRUCTORS TOO
	//Y axis offset is alaways the same
	this->yOffset = 30.f;

	//reverse X axis offset if player is facing left
	if (!isRightFacing) {
		this->xOffset = -130.f;
	} else {
		this->xOffset = 130.f;
	}
	
	this->shape.setPosition(pos.x + this->xOffset, pos.y + this->yOffset);

	//reverse shape if player is facing left
	if (!isRightFacing) {
		this->shape.scale(-1.f, 1.f);;
	}

	// DO THIS IN OTHER CONSTRUCTORS TOO ENDS

	//USED ONLY IN DEBUG
	this->startupTimeMax = 10;
	this->lifespanMax = 6;
	this->targetH = TargetHeight::HIGH;
	this->onHitStagger = 8;

	this->onBlockStagger = 5;
	this->onHitRecovery = 7;

	this->onBlockRecovery = 12;
	this->onMissRecovery = 14;

	this->dmg = 10;
	this->knockback = 40;
	this->knockup = -20;
	//USED ONLY IN DEBUG ENDS
	
}

AttackMove::~AttackMove() {

}

const int AttackMove::getOnHitStagger() const {
	return this->onHitStagger;
}

const int AttackMove::getOnBlockStagger() const {
	return this->onHitStagger;
}

const TargetHeight AttackMove::getTargetHeight() const {
	return this->targetH;
}

const int AttackMove::getDmg() const {
	return this->dmg;
}

const bool AttackMove::getWasHitRegistered() const {
	return this->wasHitRegistered;
}

const bool AttackMove::getDidMiss() const {
	return this->didMiss;
}

const int AttackMove::getKnockback() const {
	return this->knockback;
}

const int AttackMove::getKnockup() const {
	return this->knockup;
}

const bool AttackMove::getIsActive() const {
	return this->isActive;
}

bool AttackMove::getHasEnded() {
	return (this->lifespan >= this->lifespanMax);
}

const sf::RectangleShape& AttackMove::getShape() const {
	return this->shape;
}

void AttackMove::throwAttack() {
	this->isActive = true;
	
}

void AttackMove::registerHit() {
	this->wasHitRegistered = true;
}

void AttackMove::endAttack() {
	//TODO
	this->isActive = false;
}

void AttackMove::update() {
	if (!this->isActive) {
		if (!this->wasHitRegistered) {
			++this->startupTime;
		}
	} else {
		++this->lifespan;
	}
	if (this->startupTime >= this->startupTimeMax && !isActive && !this->wasHitRegistered) {
		this->throwAttack();
	}
	if (this->lifespan >= this->lifespanMax) {
		this->endAttack();
	}
}

void AttackMove::render(sf::RenderTarget* target) {
	if (this->isActive) {
		target->draw(this->shape);
	}
	
}

void AttackMove::initVariables() {
	//those values are alaways the same initially
	//potentialy run only in copy constuctor
	this->startupTime = 0;
	this->lifespan = 0;
	this->wasHitRegistered = false;
	this->isActive = false;
	this->didMiss = false;
}

