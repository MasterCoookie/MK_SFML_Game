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

void GameObject::initTexture(std::string textureName) {
	//load texture form file
	if (!this->texture.loadFromFile("./Textures/" + textureName)) {
		std::cout << "ERR: PLAYER::INITTEXTURE: Could not load texture file" << std::endl;
	}
}

void GameObject::initSprite() {
	//set sprite texture
	this->sprite.setTexture(this->texture);

	//scale sprite
	this->sprite.scale(.5f, .5f);
}

void GameObject::initVariables() {

}
