#pragma once
#include "GameObject.h"

enum Position { STANDING, DUCKING, AIRBORNE };

class Player : public GameObject {
public:
	Player();
	Player(std::string charName);
	~Player();
	
	//modifiers
	void setRightFacing(bool facing);
	void setMovementMatrix(bool forward, bool back, bool up, bool down, bool lHand, bool rHand, bool kick);
	void resetMovementMatrix();
	

	//getters
	const bool rightFacing();
	const bool getMovementMatrix();
	
	//overrides
	void update() override;
	void render(sf::RenderTarget* target) override;
	
	//methods
	bool canMove();
	void move();
	void jump();
	void duck();

	//updates
	void updateMovement();

private:
	//properties
	enum Position position;
	bool isRightFacing;
	float xAxisMomentum;
	float yAxisMomentum;

	bool movementMatrix[7] = { 0 };

	//inits
	void initVariables() override;
	
};