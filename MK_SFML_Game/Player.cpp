#include "Player.h"

Player::Player() {
	this->initVariables();
}

Player::Player(std::string charName) {
	this->initVariables();
	// init player baset on character name
	this->initTexture("./Characters/" + charName + "/tex.png");
	this->initSprite();
}

Player::~Player() {

}

void Player::setRightFacing(bool facing) {
	this->isRightFacing = facing;
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
	memset(this->movementMatrix, 0, 7);
}

void Player::move() {
	const int movementSpeed = 14;
	if (this->isRightFacing) {
		this->sprite.move(this->movementMatrix[0] * movementSpeed, 0);
		this->sprite.move(-this->movementMatrix[1] * movementSpeed, 0);
	} else {
		this->sprite.move(-this->movementMatrix[0] * movementSpeed, 0);
		this->sprite.move(this->movementMatrix[1] * movementSpeed, 0);
	}
}

const bool Player::rightFacing() {
	return this->isRightFacing;
}

const bool Player::getMovementMatrix() {
	return this->movementMatrix;
}

void Player::update() {

}

void Player::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
}

bool Player::canMove() {
	//TODO - develop further
	return !this->isAirborne;
}

void Player::initVariables() {
	this->isAirborne = false;
	this->xAxisMomentum = 0;
}
