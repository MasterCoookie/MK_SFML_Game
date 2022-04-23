#include "AttackMove.h"

AttackMove::AttackMove() {
	this->initVariables();
}

AttackMove::~AttackMove() {

}

void AttackMove::initVariables() {
	//those values are alaways the same initially
	//potentialy run only in copy constuctor
	this->startupTime = 0;
	this->lifespan = 0;
	this->wasHitRegistered = false;
}

