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
	void setState(const State& state);
	

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
	void block();
	void dropBlock(const bool continueDucking);
	void stagger(const State state, const float frames);
	// sets currentAttack. returns true if key combo matched, false if it didnt
	bool selectAttack();
	void attack();
	void takeHit(AttackMove& hitBy);

	//updates
	void updateMovement();
	void updateAttack();
	void updateStagger();

private:
	//properties
	//positions and state
	enum Position position;
	enum State state;
	bool isRightFacing;
	float xAxisMomentum;
	float yAxisMomentum;

	float hpMax;
	float hp;

	float staggerFrames;

	//textures
	sf::Texture duckingTexture;
	sf::Texture jumpingTexture;
	sf::Texture blockingTexture;
	sf::Texture blockingDuckTexture;

	bool movementMatrix[7] = { 0 };

	//copy of an attack
	AttackMove currentAttack;

	//inits
	void initVariables() override;

	//private methods
	bool wasAttackBlocked(const AttackMove& hitBy);
	
	std::string charName;
};