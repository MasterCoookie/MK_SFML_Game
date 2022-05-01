#include "Animator.h"



Animator::Animator(sf::IntRect* _textureRectPtr, int _xMax, int _yMax, AnimationType aType) : textureRectPtr(_textureRectPtr), xMax(_xMax), yMax(_yMax), currAnimation(aType) {
	this->initVariables();
}

Animator::~Animator() {

}

void Animator::update() {
	this->textureRectPtr->left += 150;
}

void Animator::initVariables() {
	this->xInterval = 150;
	this->yIntervall = 0;
}

