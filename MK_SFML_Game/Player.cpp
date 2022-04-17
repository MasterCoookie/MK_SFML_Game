#include "Player.h"

Player::Player() {
}

Player::Player(std::string charName) {
	// init player baset on character name
	this->initTexture("./Characters/" + charName + "/tex.png");
	this->initSprite();
}

Player::~Player() {

}

void Player::update() {

}

void Player::render(sf::RenderTarget* target) {
	target->draw(this->sprite);
}

bool Player::canMove() {
	//TODO - develop further
	return this->isAirborne;
}

void Player::initVariables() {
	this->isAirborne = false;
	this->xAxisMomentum = 0;
}
