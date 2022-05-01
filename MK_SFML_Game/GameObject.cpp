#include "GameObject.h"

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::setPosition(const sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

void GameObject::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

void GameObject::move(const float x, const float y) {
	this->sprite.move(x, y);
}

const sf::Vector2f& GameObject::getPosition() const {
	return this->sprite.getPosition();
}

const sf::FloatRect GameObject::getBounds() const {
	return this->sprite.getGlobalBounds();
}

void GameObject::initTexture(std::string texturePath) {
	//load texture form file
	if (!this->texture.loadFromFile(texturePath)) {
		std::cout << "ERR: GAMEOBJECT::INITTEXTURE: Could not load texture file" << std::endl;
	}
}

void GameObject::initTexture(sf::Texture& targetTexture, std::string texturePath) {
	//load texture form file
	if (!targetTexture.loadFromFile(texturePath)) {
		std::cout << "ERR: GAMEOBJECT::INITTEXTURE: Could not load texture file" << std::endl;
	}
}

void GameObject::initSprite() {
	//set sprite texture
	this->sprite.setTexture(this->texture);

	//scale sprite
	this->sprite.scale(.5f, .5f);
}

void GameObject::initSprite(int startingX, int startingY, int sizeX, int sizeY) {
	//set sprite texture
	this->textureRect = sf::IntRect(startingX, startingY, sizeX, sizeY);
	this->sprite.setTextureRect(this->textureRect);
	this->sprite.setTexture(this->texture);

	//scale sprite
	//this->sprite.scale(.5f, .5f);
}

void GameObject::initSprite(sf::IntRect intRect) {
	//set sprite texture
	this->textureRect = intRect;
	this->sprite.setTextureRect(this->textureRect);
	this->sprite.setTexture(this->texture);
}

void GameObject::initVariables() {

}
