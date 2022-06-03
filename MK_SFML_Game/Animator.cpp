#include "Animator.h"



Animator::Animator(std::shared_ptr<sf::IntRect> _textureRectPtr, int _xMax, int _yMax, AnimationType aType, bool _looping, bool _bouncing) :
	textureRectPtr(_textureRectPtr), xMax(_xMax), yMax(_yMax), currAnimation(aType), looping(_looping), bouncing(_bouncing) {
	this->xInterval = 150;
	this->initVariables();
}

Animator::Animator(std::shared_ptr<sf::IntRect> _textureRectPtr, int _xMax, int _yMax, AnimationType aType, bool _looping, bool _bouncing, int _xInterval) :
	textureRectPtr(_textureRectPtr), xMax(_xMax), yMax(_yMax), currAnimation(aType), looping(_looping), bouncing(_bouncing), xInterval(_xInterval) {
	this->initVariables();
}

Animator::~Animator() {

}

const AnimationType Animator::getCurrAnimationType() {
	return this->currAnimation;
}

void Animator::update() {
	if (this->ascending) {
		if (this->xMax > this->textureRectPtr->left + xInterval) {
			this->textureRectPtr->left += xInterval;
		} else if (this->looping) {
			if (this->bouncing) {
				this->ascending = false;
			} else {
				this->textureRectPtr->left = 0;
			}
		}
	} else if(this->looping) {
		if (this->textureRectPtr->left - xInterval >= 0) {
			this->textureRectPtr->left -= xInterval;
		}
		else if (this->looping) {
			this->ascending = true;
		}
	}
}

void Animator::initVariables() {
	this->ascending = true;
	this->yIntervall = 0;
}

