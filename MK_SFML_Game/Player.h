#pragma once

#include "AttackMove.h"
#include "Animator.h"
#include "AttackMovesMatrix.h"

enum class Position { STANDING, DUCKING, AIRBORNE, LYING };

enum class State { IDLE, BLOCKING, ATTACKING, HIT_STAGGERED, BLOCK_STAGGERED, GETTING_UP };

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
	void winRound();
	void looseRound();
	

	//getters
	const bool rightFacing();
	const bool getMovementMatrix();
	const Position getBodyPosition();
	const State getState();
	AttackMove& getCurrentAttack();
	const int getRoundsWon();
	const float getHp();
	const std::string getCharName();
	
	//overrides
	void update() override;
	void render(std::shared_ptr<sf::RenderTarget> win) override;
	
	//methods
	bool canMove();
	bool canAttack();
	void move();
	void jump();
	void duck();
	void block();
	void dropBlock(const bool continueDucking);
	void stagger(const State state, const float frames);
	void recover(const float frames);
	// sets currentAttack. returns true if key combo matched, false if it didnt
	bool selectAttack();
	void attack();
	void takeHit(AttackMove& hitBy);
	void reset();

	//updates
	void updateMovement();
	void updateAttack();
	void updateStagger();
	void updateGetUp();
	void updateRecovery();
	void updateAnimation();

	void initVariables() override;

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

	int roundsWon;

	float staggerFrames;
	float getUpFrames;
	float recoveryFrames;

	//textures
	sf::Texture* duckingTexture;
	sf::Texture* attackingTexture;

	//To map
	std::unordered_map<std::string, sf::Texture*> playerTextures;

	//pointer to animator instance
	Animator* animator;

	bool movementMatrix[7] = { 0 };

	AttackMovesMatrix* movesMatrix;

	//copy of an attack
	AttackMove currentAttack;

	//inits
	
	void initTexturesMap();

	//private methods
	bool wasAttackBlocked(const AttackMove& hitBy);
	
	std::string charName;
	std::string lockedAnimation;
};