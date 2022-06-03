#pragma once
#include "GameObject.h"

enum class AnimationType { STANDING, WALKING_F, WALKING_B, JUMPING, ATTACKING, GETTING_UP, FALLING };

class Animator {
public:
	Animator(std::shared_ptr<sf::IntRect> textureRectRef, int xMax, int yMax, AnimationType aType, bool _looping, bool _bouncing);
	Animator(std::shared_ptr<sf::IntRect> textureRectRef, int xMax, int yMax, AnimationType aType, bool _looping, bool _bouncing, int _xInterval);
	~Animator();

	//getters
	const AnimationType getCurrAnimationType();

	void update();
private:
	AnimationType currAnimation;
	std::shared_ptr<sf::IntRect> textureRectPtr;

	//private fields
	int xInterval;
	int yIntervall;
	int xMax;
	int yMax;
	bool looping;
	bool bouncing;
	bool ascending;


	void initVariables();
};