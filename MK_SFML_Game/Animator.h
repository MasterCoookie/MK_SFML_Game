#pragma once
#include "GameObject.h"

enum class ANIMATION_TYPE { STANDING, WALKING_F, WALKING_B, JUMPING};

class Animator {
public:
	Animator(sf::IntRect* textureRectRef, int xMax, int yMax);
	~Animator();

	void update();
private:
	ANIMATION_TYPE currAnimation;
	sf::IntRect* textureRectRef;

	int xInterval;
	int yIntervall;
	int xMax;
	int yMax;

	void initVariables();
};