#pragma once
#include "GameObject.h"

enum class TargetHeight { LOW, MID, HIGH, OVERHEAD };

class AttackMove : public GameObject {
public:
	AttackMove();
	~AttackMove();

	//accessors
	const int getOnHitStagger() const;
	const int getOnBlockStagger() const;
	const TargetHeight getTargetHeight() const;
	const int getDmg() const;
	const bool getWasHitRegistered() const;
	const int getKnockback() const;
	const int getKnockup() const;
	const bool getIsActive() const;

	//modifiers
	

	//methods
	//startup frames ended, activates attack, can now hit oppontent
	void throwAttack();
	//on-hit
	void registerHit();
	//active frames ended, apply recovery to player
	void endAttack();

	void update() override;

	void render(sf::RenderTarget* target) override;

private:
	//properties
	// life properties
	// how long it takes for move to become active
	int startupTimeMax;
	//how many frames has the move been starting for
	int startupTime;
	// how long does the move stay active for
	int lifespanMax;
	// for how long has the move been active for
	// !begins to increase only after the move becomes active!
	int lifespan;
	
	// aimed where?
	TargetHeight targetH;

	//only after attack becomes active - true - it can now hit
	bool isActive;

	// stagger propertiers
	// for how long is the target going to be staggered for
	int onHitStagger;
	// for how long is the target going to be staggered for after blocking
	int onBlockStagger;

	//recoeveries
	//how long for the thrower to recover after hitting oponent
	int onHitRecovery;
	//how long for the thrower to recover after hitting blocking oponent
	int onBlockRecovery;
	//how long for the thrower to recover after missing completely
	int onMissRecovery;

	//hit
	int dmg;
	bool wasHitRegistered;
	//xAxisMomentum, added on-hit
	int knockback;
	//yAxisMomentum, added on-hit
	int knockup;

	void initVariables();

};
