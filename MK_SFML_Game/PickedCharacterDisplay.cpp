#include "PickedCharacterDisplay.h"

PickedCharacterDisplay::PickedCharacterDisplay(int width, int height, bool isLeft) : SimpleGUIElement() {
	this->textureRect = std::make_shared<sf::IntRect>(0, 0, width, height);
	this->texture = std::make_shared<sf::Texture>();
	if (!this->texture->loadFromFile("./SceneMenu/players.png")) std::cout << "PLAYERS.PNG NOT FOUND";
	this->initSprite(*(this->texture), this->textureRect);
	this->animator = std::make_unique<Animator>(this->textureRect, width * 10, height * 9, AnimationType::STANDING, true, true);
	if (isLeft) {
		this->setPosition({ 50,200 });
	}
	else {
		this->setPosition({ 1280 - 50,200 });
		this->sprite.scale({ -1, 1 });
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
