#pragma once
#include "GameObject.h"

enum class Position { STANDING, DUCKING, AIRBORNE };

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
	const Position getBodyPosition();
	
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
	//positions
	enum Position position;
	bool isRightFacing;
	float xAxisMomentum;
	float yAxisMomentum;

	//textures
	sf::Texture duckingTexture;
	sf::Texture jumpingTexture;

	bool movementMatrix[7] = { 0 };

	//inits
	void initVariables() override;
	
};