#pragma once
#include "GameObject.h"

enum class AnimationType { STANDING, WALKING_F, WALKING_B, JUMPING};

class Animator {
public:
	Animator(sf::IntRect* textureRectRef, int xMax, int yMax, AnimationType aType);
	~Animator();

	void update();
private:
	AnimationType currAnimation;
	sf::IntRect* textureRectPtr;

	int xInterval;
	int yIntervall;
	int xMax;
	int yMax;

	void initVariables();
};