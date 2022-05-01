#include "Animator.h"



Animator::Animator(sf::IntRect* _textureRectPtr, int _xMax, int _yMax, AnimationType aType, bool _looping) :
	textureRectPtr(_textureRectPtr), xMax(_xMax), yMax(_yMax), currAnimation(aType), looping(_looping) {
	this->initVariables();
}

Animator::~Animator() {

}

const AnimationType Animator::getCurrAnimationType() {
	return this->currAnimation;
}

void Animator::update() {
	if (this->ascending) {
		if (this->xMax > this->textureRectPtr->left + 150) {
			this->textureRectPtr->left += 150;
		} else if (this->looping) {
			this->ascending = false;
		}
	} else if(this->looping) {
		if (this->textureRectPtr->left - 150 >= 0) {
			this->textureRectPtr->left -= 150;
		}
		else if (this->looping) {
			this->ascending = true;
		}
	}
}

void Animator::initVariables() {
	this->ascending = true;
	this->xInterval = 150;
	this->yIntervall = 0;
}

