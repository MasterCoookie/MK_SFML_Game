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

void Player::initVariables() {

}
