#include "AttackMove.h"

AttackMove::AttackMove() {
	this->initVariables();
}

AttackMove::~AttackMove() {

}

const int AttackMove::getOnHitStagger() const {
	return this->onHitStagger;
}

const int AttackMove::getOnBlockStagger() const {
	return this->onHitStagger;
}

const targetHeight AttackMove::getTargetHeight() const {
	return this->targetH;
}

const int AttackMove::getDmg() const {
	return this->dmg;
}

const bool AttackMove::getWasHitRegistered() const {
	return this->wasHitRegistered;
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

void AttackMove::throwAttack() {
	this->isActive = true;
}

void AttackMove::registerHit() {
	this->wasHitRegistered = true;
}

void AttackMove::endAttack() {
	//TODO
}

void AttackMove::update() {
	if (!this->isActive) {
		++this->startupTime;
	} else {
		++this->lifespan;
	}
	if (this->startupTime >= this->startupTimeMax) {
		this->throwAttack();
	}
	if (this->lifespan >= this->lifespanMax) {
		this->endAttack();
	}
}

void AttackMove::initVariables() {
	//those values are alaways the same initially
	//potentialy run only in copy constuctor
	this->startupTime = 0;
	this->lifespan = 0;
	this->wasHitRegistered = false;
	this->isActive = false;
}



