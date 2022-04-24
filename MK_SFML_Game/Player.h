#pragma once
#include "AttackMove.h"

enum class Position { STANDING, DUCKING, AIRBORNE };

enum class State { IDLE, BLOCKING, ATTACKING, HIT_STAGGERED, BLOCK_STAGGERED };

class Player : public GameObject {
public:
	Player();
	Player(std::string charName);
	~Player();
	
	//modifiers
	void setRightFacing(bool facing);
	void setMovementMatrix(bool lHand, bool rHand, bool kick);
	void setMovementMatrix(bool forward, bool back, bool up, bool down);
	void setMovementMatrix(bool forward, bool back, bool up, bool down, bool lHand, bool rHand, bool kick);
	void resetMovementMatrix();
	

	//getters
	const bool rightFacing();
	const bool getMovementMatrix();
	const Position getBodyPosition();
	const State getState();
	AttackMove& getCurrentAttack();
	
	//overrides
	void update() override;
	void render(sf::RenderTarget* target) override;
	
	//methods
	bool canMove();
	bool canAttack();
	void move();
	void jump();
	void duck();
	// sets currentAttack. returns true if key combo matched, false if it didnt
	bool selectAttack();
	void attack();

	//updates
	void updateMovement();

private:
	//properties
	//positions and state
	enum Position position;
	enum State state;
	bool isRightFacing;
	float xAxisMomentum;
	float yAxisMomentum;

	//textures
	sf::Texture duckingTexture;
	sf::Texture jumpingTexture;

	bool movementMatrix[7] = { 0 };

	//copy of an attack
	AttackMove currentAttack;

	//inits
	void initVariables() override;
	
};