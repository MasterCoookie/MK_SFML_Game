#pragma once
#include "GameObject.h"

enum class TargetHeight { LOW, MID, HIGH, OVERHEAD };

class AttackMove : public GameObject {
public:
	AttackMove();
	AttackMove(const sf::Vector2f pos, float xSize, float ySize, bool isRightFacing, std::string charName);
	~AttackMove();

	//accessors
	const int getOnHitStagger() const;
	const int getOnBlockStagger() const;
	const float getRecovery() const;
	const TargetHeight getTargetHeight() const;
	const int getDmg() const;
	const bool getWasHitRegistered() const;
	const bool getWasBlockRegistered() const;
	const bool getDidMiss() const;
	const int getKnockback() const;
	const int getKnockup() const;
	const bool getIsActive() const;
	bool getHasEnded();
	const sf::RectangleShape& getShape() const;
	sf::Texture* getPlayerTexture();

	//modifiers
	

	//methods
	//startup frames ended, activates attack, can now hit oppontent
	void throwAttack();
	//on-hit
	void registerHit();
	void registerBlock();
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
	// !dont read from file!
	int startupTime;
	// how long does the move stay active for
	int lifespanMax;
	// for how long has the move been active for
	// !begins to increase only after the move becomes active!
	// !dont read from file!
	int lifespan;
	
	// aimed where?
	TargetHeight targetH;

	//only after attack becomes active - true - it can now hit
	// !dont read from file!
	bool isActive;

	// stagger propertiers
	// for how long is the target going to be staggered for
	int onHitStagger;
	// for how long is the target going to be staggered for after blocking
	int onBlockStagger;

	//recoeveries
	//how long for the thrower to recover after hitting oponent
	float onHitRecovery;
	//how long for the thrower to recover after hitting blocking oponent
	int onBlockRecovery;
	//how long for the thrower to recover after missing completely
	float onMissRecovery;

	//hit
	int dmg;
	// !dont read from file!
	bool wasHitRegistered;
	// !dont read from file!
	bool wasBlockRegistered;
	// !dont read from file!
	bool didMiss;
	//xAxisMomentum, added on-hit
	int knockback;
	//yAxisMomentum, added on-hit
	int knockup;

	//offsets
	float xOffset;
	float yOffset;

	sf::RectangleShape shape;

	void initVariables();

	sf::Texture atkTexture;
	sf::Texture* playerAtkTexture;

};
