#include "PickedCharacterDisplay.h"

PickedCharacterDisplay::PickedCharacterDisplay(int width, int height, bool isLeft) : SimpleGUIElement() {
	this->textureRect = new sf::IntRect(0, 0, width, height);
	this->texture = new sf::Texture;
	if (!this->texture->loadFromFile("./SceneMenu/players.png")) std::cout << "PLAYERS.PNG NOT FOUND";
	this->initSprite(*(this->texture), this->textureRect);
	this->animator = new Animator(this->textureRect, width * 11, height * 9, AnimationType::STANDING, true, true);
	if (isLeft) {
		this->setPosition({ 50,200 });
	}
	else {
		this->setPosition({ 1280 - 210,200 });
	}
	
}
void PickedCharacterDisplay::update(int i)
{
	if (i != -1) {
		sf::IntRect recOfNew = this->getIntRect();
		recOfNew.top = i * recOfNew.height;
		this->setIntRect(*(this->texture), recOfNew);
	}
	this->animator->update();
	this->initSprite(*(this->texture), this->textureRect);
}
