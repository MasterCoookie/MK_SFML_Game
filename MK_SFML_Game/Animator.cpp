#include "Animator.h"



Animator::Animator(sf::IntRect* _textureRectRef, int xMax, int yMax) : textureRectRef(_textureRectRef) {
}

Animator::~Animator() {

}

void Animator::update() {

}

void Animator::initVariables() {
	this->xInterval = 150;
	this->yIntervall = 0;
}

