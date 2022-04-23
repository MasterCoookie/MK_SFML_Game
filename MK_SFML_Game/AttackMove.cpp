#include "AttackMove.h"

AttackMove::AttackMove() {
	this->wasThrown = false;
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

void AttackMove::throwAttack() {
	this->wasThrown = true;
}

void AttackMove::registerHit() {
	this->wasHitRegistered = true;
}

void AttackMove::update() {
	if (this->wasThrown) {

	}
	if (this->wasHitRegistered) {
		//increase counters
	}
}

void AttackMove::initVariables() {
	//those values are alaways the same initially
	//potentialy run only in copy constuctor
	this->startupTime = 0;
	this->lifespan = 0;
	this->wasHitRegistered = false;
}



