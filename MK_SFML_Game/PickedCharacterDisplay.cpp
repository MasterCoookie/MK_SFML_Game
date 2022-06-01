#include "PickedCharacterDisplay.h"

PickedCharacterDisplay::PickedCharacterDisplay(int width, int height, bool isLeft) : SimpleGUIElement() {
	this->textureRect = new sf::IntRect(0, 0, width, height);
	this->texture = new sf::Texture;
	if (!this->texture->loadFromFile("./SceneMenu/players.png")) std::cout << "PLAYERS.PNG NOT FOUND";
	this->initSprite(*(this->texture), this->textureRect);
	this->animator = new Animator(this->textureRect, width * 11, height * 9, AnimationType::STANDING, true, false);
	if (isLeft) {
		this->setPosition({ 10,100 });
	}
	else {

	}
	
}
void PickedCharacterDisplay::switchSprite(sf::Texture& tex, int top)
{
	sf::IntRect recOfNew = this->getIntRect();
	recOfNew.top = top;
	this->setIntRect(tex, recOfNew);
}
