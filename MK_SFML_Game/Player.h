#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	Player(std::string charName);
	~Player();
	
	//modifiers
	void setRightFacing(bool facing);
	void setMovementMatrix(bool forward, bool back, bool up, bool down, bool lHand, bool rHand, bool kick);
	void resetMovementMatrix();
	void move();

	//getters
	const bool rightFacing();
	const bool getMovementMatrix();
	
	//overrides
	void update() override;
	void render(sf::RenderTarget* target) override;
	
	//methods
	bool canMove();
private:
	//properties
	bool isAirborne;
	bool isRightFacing;
	float xAxisMomentum;

	bool movementMatrix[7] = { 0 };

	//inits
	void initVariables() override;
};