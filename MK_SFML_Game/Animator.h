#pragma once
#include "GameObject.h"

enum class AnimationType { STANDING, WALKING_F, WALKING_B, JUMPING};

class Animator {
public:
	Animator(sf::IntRect* textureRectRef, int xMax, int yMax, AnimationType aType, bool _looping);
	~Animator();

	//getters
	const AnimationType getCurrAnimationType();

	void update();
private:
	AnimationType currAnimation;
	sf::IntRect* textureRectPtr;

	//private fields
	int xInterval;
	int yIntervall;
	int xMax;
	int yMax;
	bool looping;
	bool ascending;


	void initVariables();
};